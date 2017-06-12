#include "songkick_parser.h"

SONGKICKparser::SONGKICKparser(QObject *parent) : QObject(parent)
{


   url_downlaod =  new URLDownload(this);
    QByteArray data_to_parse;
   QNetworkAccessManager manager;
   //QNetworkReply *response = manager.get(QNetworkRequest(QUrl("http://www.zmt.tarnow.pl/")));
   QString link = "http://last.fm/music/Autechre/+events";
   qDebug() << link;
   QNetworkReply *response = manager.get(QNetworkRequest(QUrl(link)));
   QEventLoop event;
   connect(response,SIGNAL(finished()),&event,SLOT(quit()));
   event.exec();

   data_to_parse = response->readAll();
 qDebug() << data_to_parse;

   // connect(url_downlaod, SIGNAL(data_recieved(QByteArray)), this, SLOT(on_parse_from_url(QByteArray)));
}

SONGKICKparser::~SONGKICKparser(){

    delete url_downlaod;

}

void SONGKICKparser::get_url_data(QString artist_tag)
{
    qDebug() << "get_url_data";
    url_downlaod->download_data_from_url("https://www.songkick.com/artists/3857951-lapalux");


}




void SONGKICKparser::on_parse_from_url(QByteArray data)
{

    QString str(data);
    qDebug() <<"on_parse_from_url"<< str;


}
