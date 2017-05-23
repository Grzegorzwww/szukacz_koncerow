#include "appengine.h"
#include "ui_mainwindow.h"

AppEngine::AppEngine(Ui::MainWindow *_ui, QObject *parent):ui(_ui), my_parent(parent)

{
    qDebug() << "AppEngine";

    found_events = 0;
    name_parser  = new NameParser();
    progrescounter = 0;
    find_counter = 0;

    readArtistFromLogFile("artist_log", &artist_list);
    readArtistFromLogFile("fb_artist_log", &fb_artist_list);

    connect(this, SIGNAL(lastfm_downloading_finshed(bool)), this, SLOT(on_start_facebook_clicked(bool)));
    connect(this, SIGNAL(facebook_downloading_finshed(bool )), this, SLOT(all_test_finished(bool)));
    connect(this, SIGNAL(downloading_finshed(bool )), this, SLOT(all_test_finished(bool)));

}



void AppEngine::on_start_lastfm_clicked(bool x){
    qDebug() << "on_start_lastfm_clicked";
    search_in_progres = true;
    QList<QString>::iterator i;
    progrescounter = 0;
    find_counter = 0;
    for (i = artist_list.begin(); i != artist_list.end(); ++i){
        qDebug() << *i << endl;
        QString artist_name = *i;
        emit add_message_info_label("SPRAWDZENIE [LastFm]: "+artist_name);
        emit add_to_progress_bar(++progrescounter);
        lastfm_parser = new LASTFMParser( my_parent, name_parser->generateLastFmLink(artist_name ));
        lastfm_parser->getArtistName(artist_name );
        lastfm_parser->parseDataFromHTMLFile();

        if(lastfm_parser->getMaxEventsRecords() == 0){
            fillEmptyTabResultRecord(lastfm_parser->getArtistTokenPtr(), "last.fm");
        }else {

            fillTabResultRecord(lastfm_parser->getArtistTokenPtr(), "last.fm");
        }
        find_counter += lastfm_parser->getArtistTokenPtr()->occurance_no;
        delete  lastfm_parser;
        if( search_in_progres == false){
            emit downloading_finshed(true);
            break;
        }
    }
    search_in_progres = false;
    emit lastfm_downloading_finshed(true);
}


void AppEngine::on_start_facebook_clicked(bool x){
    QList<QString>::iterator i;
    search_in_progres = true;
    int j = 0;
    qDebug() << "fb_artist_list.size() " <<fb_artist_list.size();
    for (i = fb_artist_list.begin(); i != fb_artist_list.end(); ++i  ){

        fb_artist_token = new ArtistToken();
        fb_artist_token->token_type = FACEBOOK_TOKEN;
        QString artist_name = *i;
        emit add_message_info_label("SPRAWDZENIE [Facebook]: "+artist_name);
        emit add_to_progress_bar(++progrescounter);
        fb_parser = new FBparser(my_parent, name_parser->generateFacebookLink(artist_name));
        fb_parser->getArtistName(artist_name, fb_artist_token);
        fb_parser->parseDataFromJSONFile( fb_artist_token);

        if(fb_artist_token->occurance_no == 0){
            fillEmptyTabResultRecord( fb_artist_token, "facebook");
        }
        else if(fb_artist_token->occurance_no > 0){
            fillTabResultRecord( fb_artist_token, "facebook");
        }
        find_counter += fb_artist_token->occurance_no;
        delete fb_parser;
        delete fb_artist_token;
        if( search_in_progres == false){
            emit downloading_finshed(true);
            break;
        }
    }
    search_in_progres = false;
    emit  facebook_downloading_finshed(true);
}


void AppEngine::all_test_finished(bool x){
    int all_artist = artist_list.size() + fb_artist_list.size();
    add_message_info_label("Zakonczono przeszukiwanie "+QString::number(all_artist)+" wykonawcow. Znaleziono: "+QString::number(find_counter)+" koncerów");

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
void AppEngine::on_reload_artist_list(){
    qDebug() << "on_reload_artist_list";
    artist_list.clear();
    fb_artist_list.clear();
    readArtistFromLogFile("artist_log", &artist_list);
    readArtistFromLogFile("fb_artist_log", &fb_artist_list);
}











