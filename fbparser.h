#ifndef FBPARSER_H
#define FBPARSER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QObject>
#include <string>
#include <QByteArray>
#include <QDateTime>
#include <iostream>
#include <event_token.h>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


class FBparser : public QObject
{
      Q_OBJECT
public:
    explicit FBparser(QObject *parent, QString link);
    ~FBparser();

    void getArtistName(QString str, ArtistToken *artist_token);
    void parseDataFromJSONFile(ArtistToken *artist_token);
    void resetTokenCounter() {tokens_counter = 0;}
    QString generateEventRecord(int no, ArtistToken *artist_token);
    QString generateEventRecord_2(int no, ArtistToken *artist_token);
    QString compensText(QString text, int total_space, int ofset);




private :

    QString link_to_parse;

    QByteArray *json_data_to_parse;
    QNetworkReply *response;


    int tokens_counter;


    QNetworkAccessManager *m_manager;
    void fetch();



public slots:
     void replyFinished(QNetworkReply*);

signals:
     void downloading_complete(void);
};

#endif // FBPARSER_H
