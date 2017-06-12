#include "search_artist.h"

search_artist::search_artist(QObject *parent ) : QObject(parent)
{

    find_artis_token.name = "No available";
    find_artis_token.listeners = 0;
    find_artis_token.url  = "No available";
    //find_artis_token.image_url  = "No available";


    //last_fm_search = false;


    url_downlaod = new URLDownload(this);
    fb_url_downlaod = new URLDownload(this);
    fb_url_specyfic_data_downlaod = new URLDownload(this);




   connect(url_downlaod, SIGNAL(data_recieved(QByteArray)), this, SLOT(on_data_downloaded(QByteArray)));
   connect(fb_url_downlaod, SIGNAL(data_recieved(QByteArray)), this, SLOT(on_fb_data_downloaded(QByteArray)));
   connect( fb_url_specyfic_data_downlaod, SIGNAL(data_recieved(QByteArray)), this, SLOT(on_fb_specyfic_data_downloaded(QByteArray)));
}

search_artist::~search_artist(){

    delete url_downlaod;
}


void search_artist::on_data_downloaded(QByteArray data){

    if(!data.isEmpty()){
        parse_JSON_from_last_fm(data);
    }
    else {
        qDebug() <<"Error: Fail to get web content ";
    }
}

void search_artist::on_fb_data_downloaded(QByteArray data){
    qDebug() << "fb_data_downloaded:";
    qDebug() <<data;

    parse_JSON_from_Facebook(data);

}


 void search_artist::on_fb_specyfic_data_downloaded(QByteArray data){



     QJsonDocument document = QJsonDocument::fromJson(data);
     QJsonObject event_obj = document.object();
     QString url = event_obj["picture"].toObject()["data"].toObject()["url"].toString();

     find_artis_token.pix_url =  url;
     qDebug() <<"pic url" << url;

     emit facebbok_artist_finded ( find_artis_token);




 }





//https://graph.facebook.com/103078383058479?fields=id,name,picture&access_token=EAACEdEose0cBAKPhrLzJOlpZA25fHwdCwWPekw7Cr8j1NrJ1EKl2pmeRSzZCcmqBUjrMN4jpbZBN4TUHMhBW8tnPGiyVBMg249Am3cygZCPGMXbCDzL6hhEoBLEfTMqqMEULzZBi9VI0LOIZCa7zQi0yRejZCGNaZCaQEfFRZCNSZCpHq4MjBgBrE5tqFB5IpJwVAZD

 void search_artist::get_find_Lastfm_artist_token(QString name){

    QString link = "http://ws.audioscrobbler.com/2.0?method=artist.search&artist="+name+"&api_key="+LAST_FM_API_KEY+"&format=json";
    url_downlaod->download_data_from_url(link);
}




 void search_artist::get_find_Facebook_artist_token(QString name){

    name.replace(" ", "");
    QString link = "https://graph.facebook.com/search?q="+name+"&type=page&access_token="+FACEBBOK_USER_KEY;
    qDebug() <<"dupa"<<link;
    fb_url_downlaod->download_data_from_url(link);


}


void search_artist::parse_JSON_from_Facebook(QByteArray data_to_parse){


    QJsonDocument document = QJsonDocument::fromJson(data_to_parse);
    QJsonObject event_obj = document.object();
    QJsonArray artist_array = event_obj["data"].toArray();

    QJsonObject _obj =  artist_array[0].toObject();
    QString name = _obj["name"].toString();
    QString category = _obj["category"].toString();
    QString id = _obj["id"].toString();


    find_artis_token.name ="["+ name+"]"+id;
    find_artis_token.category = category;
    find_artis_token.url = "https://facebook.com/"+id;
    qDebug() << "name"<<name;
      qDebug() << "category"<<category;
    qDebug() << "id"<<id;


    QString specyfic_data_request_link = "https://graph.facebook.com/"+id+"?fields=id,name,picture&access_token="+FACEBBOK_USER_KEY;
    fb_url_specyfic_data_downlaod->download_data_from_url( specyfic_data_request_link);






}

void search_artist::parse_JSON_from_last_fm(QByteArray data_to_parse){

    QJsonDocument document = QJsonDocument::fromJson(data_to_parse);
    QJsonObject event_obj = document.object();
    QJsonArray artist_array = event_obj["results"].toObject()["artistmatches"].toObject()["artist"].toArray();

    QJsonObject _obj =  artist_array[0].toObject();
    QString temp= _obj["name"].toString();
    qDebug() << temp <<" listeners: " <<  _obj["listeners"].toString().toInt();
    find_artis_token.name = _obj["name"].toString();
    find_artis_token.listeners = _obj["listeners"].toString().toInt();
    find_artis_token.url = _obj["url"].toString();
    QJsonArray image_array = _obj["image"].toArray();
    QJsonObject img_obj = image_array[2].toObject();
    find_artis_token.pix_url = img_obj["#text"].toString();
    qDebug() << "img = " << img_obj["#text"].toString();

    emit last_fm_artist_finded( find_artis_token);

}
