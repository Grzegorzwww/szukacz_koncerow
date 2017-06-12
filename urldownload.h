#ifndef URLDOWNLOAD_H
#define URLDOWNLOAD_H

#include <iostream>
#include <QDebug>
#include <QByteArray>
#include <QObject>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class URLDownload : public QObject
{
    Q_OBJECT
public:
    explicit URLDownload(QObject *parent = 0);
    ~URLDownload();


     void download_data_from_url(QString link);

private:
     QNetworkAccessManager * m_netwManager;
     QByteArray received_data;



signals:

     void data_recieved(QByteArray data);


public slots:
      void slot_netwManagerFinished(QNetworkReply *reply);
};

#endif // URLDOWNLOAD_H
