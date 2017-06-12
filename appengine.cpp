#include "appengine.h"
#include "ui_mainwindow.h"

AppEngine::AppEngine(Ui::MainWindow *_ui, QObject *parent):ui(_ui), my_parent(parent)

{
    qDebug() << "AppEngine";

    found_events = 0;
    name_parser  = new NameParser();
    progrescounter = 0;
    find_counter = 0;
    search_in_progres = true;

    file_manager = new filemanager();
    search_for_artist = new search_artist(my_parent);

    file_manager->read_artist_list(lista_wykonawcow);
    emit actualize_artist_list();



    songkick_parser = new SONGKICKparser(this);


    suffix_to_search[0] = "music";
    suffix_to_search[1] = "musician";
    suffix_to_search[2] = "official";
    suffix_to_search_state = 0;





    //search_for_artist->get_find_Facebook_artist_token("cold cut");

    connect(search_for_artist, SIGNAL(last_fm_artist_finded(find_artist_t)), this, SLOT(on_last_fm_artist_finded(find_artist_t)));
    connect(search_for_artist, SIGNAL(facebbok_artist_finded(find_artist_t)), this, SLOT(on_facebook_artist_finded(find_artist_t)));


}

QList <artist_names_t> *  AppEngine::returnAtristListAdress(){

    return &lista_wykonawcow;
}


void AppEngine::on_start_search_last_fm_artist(QString  artist_name){

    actual_searching_artist_name =  artist_name;
     search_for_artist->get_find_Lastfm_artist_token( artist_name);

}


 void AppEngine::on_start_search_facebook_artist(QString artist_name){
     actual_searching_artist_name =  artist_name;

     search_for_artist->get_find_Facebook_artist_token(artist_name);
 }


void AppEngine::on_start_search_facebook_other_tag(){

    qDebug() << "on_start_search_facebook_other_tag()";
    switch(suffix_to_search_state){
    case 0:
        search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name+suffix_to_search[suffix_to_search_state]);
        suffix_to_search_state = 1;
        break;
    case 1:
        search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name+suffix_to_search[suffix_to_search_state]);
        suffix_to_search_state = 2;
        break;
    case 2:
        search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name+suffix_to_search[suffix_to_search_state]);
        suffix_to_search_state = 3;
        break;
   case 3:
        if(actual_searching_artist_name.contains(" ")){
            qDebug() << actual_searching_artist_name.split(" ").at(0);
            search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(0));
        }
        suffix_to_search_state = 4;
        break;
   case 4:
        if(actual_searching_artist_name.contains(" ")){
             qDebug() << actual_searching_artist_name.split(" ").at(1);
            search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(1));
        }
        suffix_to_search_state = 5;

        break;
   case 5:
        if(actual_searching_artist_name.contains(" ")){
            qDebug() << actual_searching_artist_name.split(" ").at(0);
            search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(0)+"official");
        }
        suffix_to_search_state = 6;
        break;
    case 6:
         if(actual_searching_artist_name.contains(" ")){
             qDebug() << actual_searching_artist_name.split(" ").at(1);
             search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(1)+"official");
         }
         suffix_to_search_state = 7;
         break;
    case 7:
         if(actual_searching_artist_name.contains(" ")){
             qDebug() << actual_searching_artist_name.split(" ").at(0);
             search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(0)+"music");
         }
         suffix_to_search_state = 8;
         break;
     case 8:
          if(actual_searching_artist_name.contains(" ")){
              qDebug() << actual_searching_artist_name.split(" ").at(1);
              search_for_artist->get_find_Facebook_artist_token(actual_searching_artist_name.split(" ").at(1)+"music");
          }
          suffix_to_search_state = 0;
          break;




    }
}


void AppEngine::on_concert_find_counter(void){
     find_counter ++;
}



void AppEngine::on_start_search(bool){
        ui->tabWidget->setCurrentIndex(1);
        if(!lista_wykonawcow.isEmpty()){
             QList<artist_names_t>::iterator i;
            for (i = lista_wykonawcow.begin(); i != lista_wykonawcow.end(); ++i){
                if(i->lastfm_name != "-"){
                    add_message_info_label("Pobieranie z Last.fm -> "+i->lastfm_name);
                    on_parse_lastfm_artist(i->lastfm_name);
                }
                 emit event_searching_finished( ++progrescounter);
                if(i->fb_name != "-"){
                    add_message_info_label("Pobieranie z Facebook.com -> "+i->fb_name);

                    i->fb_name.remove(QRegExp("\\[(.*)\\]"));

                    on_parse_facebook_artist(i->fb_name, i->full_name );
                }

                emit event_searching_finished( ++progrescounter);

                if( !search_in_progres){
                    search_in_progres = true;
                    break;
                }
            }
        }
        add_message_info_label("Zakończono wyszukiwanie, znaleziono koncertów: "+
                               QString::number(find_counter)+" / "+QString::number(lista_wykonawcow.size())+
                               " wykonawców" );
}


void AppEngine::on_start_search_only_selected(QList<int> list_to_display){
    int j = 0;
    if(list_to_display.size() > 0){
        if(!lista_wykonawcow.isEmpty()){
            QList<int>::iterator i;

            for (i = list_to_display.begin(); i != list_to_display.end(); ++i){

                if(lista_wykonawcow.at(*i).lastfm_name != "-"){
                    add_message_info_label("Pobieranie z Last.fm -> "+lista_wykonawcow.at(*i).lastfm_name);
                    on_parse_lastfm_artist(lista_wykonawcow.at(*i).lastfm_name);
                }
                emit event_searching_finished( ++progrescounter);
                if(lista_wykonawcow.at(*i).fb_name != "-"){
                    add_message_info_label("Pobieranie z Facebook.com -> "+lista_wykonawcow.at(*i).fb_name);

                     artist_names_t temp_artist = lista_wykonawcow.at(*i);
                    temp_artist.fb_name.remove(QRegExp("\\[(.*)\\]"));

                    on_parse_facebook_artist( temp_artist.fb_name,  temp_artist.full_name );
                }

                emit event_searching_finished( ++progrescounter);

                if( !search_in_progres){
                    search_in_progres = true;
                    break;
                }
            }
        }
        add_message_info_label("Zakończono wyszukiwanie, znaleziono koncertów: "+
                               QString::number(find_counter)+" / "+QString::number(lista_wykonawcow.size())+
                               " wykonawców" );



    }
}


void AppEngine::on_last_fm_artist_finded(find_artist_t token){
     emit last_fm_artis_find(token);
}
void AppEngine::on_facebook_artist_finded(find_artist_t token){
     emit  facebook_artis_find(token);
}




bool AppEngine::on_parse_lastfm_artist(QString artist_tag){

        lastfm_parser = new LASTFMParser( my_parent, name_parser->generateLastFmLink(artist_tag ));
        lastfm_parser->getArtistName(artist_tag );
        lastfm_parser->parseDataFromHTMLFile();
        if(lastfm_parser->getMaxEventsRecords() == 0){
            fillEmptyTabResultRecord(lastfm_parser->getArtistTokenPtr(), "last.fm");
            return false;
        }else {

            fillTabResultRecord(lastfm_parser->getArtistTokenPtr(), "last.fm");
            return true;
        }
        delete  lastfm_parser;
}

bool AppEngine::on_parse_facebook_artist(QString tag, QString pre_tag){
    int j = 0;
        fb_artist_token = new ArtistToken();
        fb_artist_token->token_type = FACEBOOK_TOKEN;
        fb_parser = new FBparser(my_parent, name_parser->generateFacebookLink(tag));
        fb_parser->getArtistName(tag, fb_artist_token);
        fb_parser->parseDataFromJSONFile( fb_artist_token);
        if(fb_artist_token->occurance_no == 0){
            fb_artist_token->articst_name =  pre_tag;
            fillEmptyTabResultRecord( fb_artist_token, "facebook");
            delete fb_parser;
            delete fb_artist_token;
            return false;
        }
        else if(fb_artist_token->occurance_no > 0){
            fb_artist_token->articst_name =  pre_tag;
            fillTabResultRecord( fb_artist_token, "facebook");
            delete fb_parser;
            delete fb_artist_token;
             return true;

        }
    return false;
}


void AppEngine::all_test_finished(bool x){

}


bool AppEngine::fillTabResultRecord( ArtistToken *artist_token, QString source){

    artist_token->source = source;
    emit artist_record(*artist_token);
}

bool AppEngine::fillEmptyTabResultRecord(ArtistToken *artist_token, QString source){
    artist_token->source = source;
    emit empty_artist_record(*artist_token);
}


void AppEngine::on_stop_searching_clicked(bool x){
    search_in_progres = false;
}


void AppEngine::on_add_artist(artist_names_t token){
     lista_wykonawcow.append(token);
     file_manager->save_artist_list(lista_wykonawcow);
     emit actualize_artist_list();
}

void AppEngine::on_remove_artist(int x){
     lista_wykonawcow.removeAt(x);
     file_manager->save_artist_list(lista_wykonawcow);
     emit actualize_artist_list();
}












