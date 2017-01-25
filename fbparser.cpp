#include "fbparser.h"


FBparser::FBparser(QObject *parent, QString link) : QObject(parent)
{

    tokens_counter = 0;


    QNetworkAccessManager manager;
    qDebug() << link;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(link)));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    json_data_to_parse = new QByteArray(response->readAll());

    QString str(*json_data_to_parse);
    //qDebug() << str;
}

FBparser::~FBparser(){
    // delete m_manager;

}

void FBparser::fetch()
{

    // m_manager->get(QNetworkRequest(QUrl(link_to_parse)));
}


void FBparser::replyFinished(QNetworkReply* pReply)
{


}

void FBparser::getArtistName(QString str, ArtistToken *artist_token){
    artist_token->articst_name = str;
}

void FBparser::parseDataFromJSONFile(ArtistToken *artist_token){

    artist_token->occurance_no = 0;
    QJsonDocument document = QJsonDocument::fromJson(*json_data_to_parse);
    QJsonObject events = document.object()["events"].toObject();
    QJsonArray events_data_array = events["data"].toArray();
    QJsonObject event_obj, event_place;
    QDateTime date;
    QString start_time_str;

    int i = 0;
    foreach(const QJsonValue &value, events_data_array ){
        event_obj = value.toObject();
        //qDebug() << event_obj["description"].toString();
        artist_token->events_name[i] = event_obj["name"].toString();

        start_time_str = event_obj["start_time"].toString();
        start_time_str = start_time_str.remove(start_time_str.length() - 5, 5);
        date = QDateTime::fromString(start_time_str, "yyyy-MM-ddTHH:mm:ss");
        artist_token->events_date[i] = date.toString("dd-MM-yyyy HH:mm:ss");

        //qDebug() << date.toString("dd-MM-yyyy HH:mm:ss");
        event_place = event_obj["place"].toObject();

        artist_token->events_city[i] =  event_place["location"].toObject()["city"].toString();
        artist_token->events_country[i] =  event_place["location"].toObject()["country"].toString();
        artist_token->occurance_no++;
        i++;

    }
}
QString FBparser::generateEventRecord(int no, ArtistToken *artist_token){
    if(artist_token->occurance_no == 0){
        QString temp_str = "FACEBOOK: ";
        temp_str = temp_str + compensText(artist_token->articst_name, 30, 1);
        temp_str = temp_str + compensText(" - Nie odnaleziono wydarzenia dla tego wykonawcy .", 50, 1);
        return temp_str;
    } else {
        QString temp_str = "FACEBOOK: ";
        temp_str = temp_str + compensText(artist_token->articst_name, 20, 1);
        temp_str = temp_str + compensText(artist_token->events_date[no], 40, 1);
        temp_str = temp_str + compensText(artist_token->events_name[no], 50, 1);
        temp_str = temp_str + compensText(artist_token->events_city[no], 40, 1);
        temp_str = temp_str + compensText(artist_token->events_country[no], 30, 1);
        qDebug() << temp_str;
        return temp_str;
    }
}

QString FBparser::generateEventRecord_2(int no, ArtistToken *artist_token){

        QString temp_str = "FACEBOOK: ";
//        temp_str = temp_str + compensText(artist_token->articst_name, 20, 1);
//        temp_str = temp_str + compensText(artist_token->events_date[no], 50, 1);
//        temp_str = temp_str + compensText(artist_token->events_name[no], 50, 1);
//        temp_str = temp_str + compensText(artist_token->events_city[no], 40, 1);
//        temp_str = temp_str + compensText(artist_token->events_country[no], 30, 1);
//        qDebug() << temp_str;
//        return temp_str;

}


QString FBparser::compensText(QString text, int total_space, int ofset){
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



