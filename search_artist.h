#ifndef SEARCH_ARTIST_H
#define SEARCH_ARTIST_H

#include <iostream>
#include <QDebug>
#include <QObject>
#include <urldownload.h>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include "defines.h"


//static const QString FACEBBOK_USER_KEY = "EAACEdEose0cBAKPhrLzJOlpZA25fHwdCwWPekw7Cr8j1NrJ1EKl2pmeRSzZCcmqBUjrMN4jpbZBN4TUHMhBW8tnPGiyVBMg249Am3cygZCPGMXbCDzL6hhEoBLEfTMqqMEULzZBi9VI0LOIZCa7zQi0yRejZCGNaZCaQEfFRZCNSZCpHq4MjBgBrE5tqFB5IpJwVAZD";
static const QString FACEBBOK_USER_KEY = "1416908014988033|f1yivkfZWkWN2QXvi8CXj_9Pdwk";



//https://graph.facebook.com/search?q=coldcut&type=page&access_token=EAACEdEose0cBAKPhrLzJOlpZA25fHwdCwWPekw7Cr8j1NrJ1EKl2pmeRSzZCcmqBUjrMN4jpbZBN4TUHMhBW8tnPGiyVBMg249Am3cygZCPGMXbCDzL6hhEoBLEfTMqqMEULzZBi9VI0LOIZCa7zQi0yRejZCGNaZCaQEfFRZCNSZCpHq4MjBgBrE5tqFB5IpJwVAZD

static const QString LAST_FM_API_KEY = "b77a84a5a5adfd12ffb6de2fbed4451b";

class search_artist : public QObject
{
     Q_OBJECT
public:

     explicit search_artist(QObject *parent);
     ~search_artist();

    QNetworkAccessManager * m_netwManager;


    void get_find_Lastfm_artist_token(QString name);
    void get_find_Facebook_artist_token(QString name);


private:

     find_artist_t find_artis_token;



     URLDownload *url_downlaod;
     URLDownload *fb_url_downlaod;
     URLDownload *fb_url_specyfic_data_downlaod;




     void parse_JSON_from_last_fm(QByteArray data_to_parse);
     void parse_JSON_from_Facebook(QByteArray data_to_parse);



public slots:

     void on_data_downloaded(QByteArray data);
     void on_fb_data_downloaded(QByteArray data);
     void on_fb_specyfic_data_downloaded(QByteArray data);


signals:


     void last_fm_artist_finded(find_artist_t );
     void facebbok_artist_finded(find_artist_t );

};

#endif // SEARCH_ARTIST_H
