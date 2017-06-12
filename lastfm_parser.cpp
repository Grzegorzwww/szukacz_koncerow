#include "lastfm_parser.h"

using namespace std;

LASTFMParser::LASTFMParser(QObject *parent, QString link) : QObject(parent)
{

    artist_token = new ArtistToken();
    artist_token->token_type = LASTFM_TOKEN;
    QNetworkAccessManager manager;
    //QNetworkReply *response = manager.get(QNetworkRequest(QUrl("http://www.zmt.tarnow.pl/")));
    qDebug() << link;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(link)));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();

    data_to_parse = response->readAll();
    qDebug() << data_to_parse;



    removePolishCharacters(&data_to_parse);

}



void LASTFMParser::parseDataFromHTMLFile(void){
    int i;
    bool web_content_flag = false;
    if(data_to_parse.isEmpty()){
        qDebug() <<"Error: Fail to get web content ";
        web_content_flag = false;
    }
    if(data_to_parse.contains("We don't have any upcoming events for")){
        qDebug() <<"There is no event for this artist";
        web_content_flag = true;
    }
    else {
        i = 0;
        web_content_flag = true;
        artist_token->occurance_tab[i] = data_to_parse.indexOf("<time datetime=", 0);
        saveEventDate(&artist_token->events_date[i], artist_token->occurance_tab[i]);
        saveEventName(&artist_token->events_name[i], artist_token->occurance_tab[i]);
        artist_token->events_name[i].replace(" ", "");
        saveEventCity(&artist_token->events_city[i], artist_token->occurance_tab[i]);
        saveEventCountry(&artist_token->events_country[i], artist_token->occurance_tab[i]);
        //qDebug()<< "data = " << artist_token->events_date[i];
        artist_token->events_date[i].replace(" ", "");
        //qDebug()<< "name = " << artist_token->events_name[i];
        artist_token->events_name[i].replace(" ", "");
        //qDebug()<< "city = " << artist_token->events_city[i];
        artist_token->events_city[i].replace("  ", " ");
        //qDebug()<< "country = " << artist_token->events_country[i];
        artist_token->events_country[i].replace("  ", " ");
        generateEventRecord(i);


        if(web_content_flag){
            while( artist_token->occurance_tab[i] != -1){
                i++;
                artist_token->occurance_no++;
                artist_token->occurance_tab[i] = data_to_parse.indexOf("<time datetime=", artist_token->occurance_tab[i- 1]+ 15);
                saveEventDate(&artist_token->events_date[i], artist_token->occurance_tab[i]);
                artist_token->events_date[i].replace("  ", "");
                saveEventName(&artist_token->events_name[i], artist_token->occurance_tab[i]);
                artist_token->events_name[i].replace("  ", "");
                saveEventCity(&artist_token->events_city[i], artist_token->occurance_tab[i]);
                artist_token->events_city[i].replace("  ", " ");
                saveEventCountry(&artist_token->events_country[i], artist_token->occurance_tab[i]);
                artist_token->events_country[i].replace("  ", " ");
            }
            for(i = 0; i < artist_token->occurance_no; i++){
                // qDebug() << QString::number(artist_token->occurance_tab[i]);
                //            qDebug()<< "data = " << artist_token->events_date[i];
                //            qDebug()<< "name = " << artist_token->events_name[i];
                //            qDebug()<< "city = " << artist_token->events_city[i];
                //            qDebug()<< "country = " << artist_token->events_country[i];
                generateEventRecord(i);

            }

        }
    }
}

void LASTFMParser::saveEventDate(QString *str, long position){
    int i;
    for(i = 0; i < 10; i++){
        str->append( data_to_parse.at(position+i+16).toLatin1());
    }
}

void LASTFMParser::saveEventName(QString *str, long position){
    int i;

    long index = data_to_parse.indexOf("events-list-item-venue--title", position);
    for(i = 0; i < 60; i++){

       if(data_to_parse.at(index+i+31).toLatin1() == '\n'){
            continue;
        }
        else if(data_to_parse.at(index+i+31).toLatin1() == '<'){
            break;
        }
        str->append( data_to_parse.at(index+i+31).toLatin1());
    }

}

void LASTFMParser::saveEventCity(QString *str, long position){
    int i;
    long index = data_to_parse.indexOf("events-list-item-venue--city", position);
    for(i = 0; i < 60; i++){

        if(data_to_parse.at(index+i+30).toLatin1() == '<'){
                    break;
        }
        str->append( data_to_parse.at(index+i+30).toLatin1());
    }

}
void LASTFMParser::saveEventCountry(QString *str, long position){
    int i;
    long index = data_to_parse.indexOf("events-list-item-venue--country", position);
    for(i = 0; i < 60; i++){
        if(data_to_parse.at(index+i+33).toLatin1() == '<'){
                    break;
        }
        str->append( data_to_parse.at(index+i+33).toLatin1());
    }

}

QString LASTFMParser::generateEventRecord(int no){


    if(artist_token->occurance_no == 0){
        QString temp_str = "LAST.FM: ";
        temp_str = temp_str + compensText(artist_token->articst_name, 30, 1);
        temp_str = temp_str + compensText(" - Nie odnaleziono wydarzenia dla tego wykonawcy.", 60, 1);
        return temp_str;
    } else {

        QString temp_str = "LAST.FM: ";
        temp_str = temp_str + compensText(artist_token->articst_name, 20, 1);
        temp_str = temp_str + compensText(artist_token->events_date[no], 15, 1);
        temp_str = temp_str + compensText(artist_token->events_name[no], 50, 1);
        temp_str = temp_str + compensText(artist_token->events_city[no], 40, 1);
        temp_str = temp_str + compensText(artist_token->events_country[no], 30, 1);
        qDebug() << temp_str;
        return temp_str;

    }
}



QString LASTFMParser::compensText(QString text, int total_space, int ofset){
    int i;
    QString temp_str = " ";
    if(ofset + text.length() < total_space){
        for(i = 0; i <= total_space; i++){
            if(i == ofset -1){
                temp_str += text;
                i = text.length()+ ofset;
            }
            else temp_str += ' ';
        }
    }
    return temp_str;
}

void LASTFMParser::removePolishCharacters(QString *str){

    str->replace("Ą","A");
    str->replace("Ć","C");
    str->replace("Ę","E");
    str->replace("Ł","L");
    str->replace("Ń","N");
    str->replace("Ó","O");
    str->replace("Ś","S");
    str->replace("Ź","Z");
    str->replace("Ż","Z");
    str->replace("ą","a");
    str->replace("ć","c");
    str->replace("ę","e");
    str->replace("ł","l");
    str->replace("ń","n");
    str->replace("ó","o");
    str->replace("ś","s");
    str->replace("ź","z");
    str->replace("ż","z");

}
void LASTFMParser::getArtistName(QString str){
   artist_token->articst_name = str;
}

int LASTFMParser::getMaxEventsRecords(void){
    return artist_token->occurance_no;
}


