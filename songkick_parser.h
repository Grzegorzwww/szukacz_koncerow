#ifndef SONGKICK_PARSER_H
#define SONGKICK_PARSER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <urldownload.h>

class SONGKICKparser : public QObject
{
    Q_OBJECT
public:
    explicit SONGKICKparser(QObject *parent = 0);
    ~SONGKICKparser();

    void get_url_data(QString artist_tag);


private:


      URLDownload *url_downlaod;




signals:

public slots:


      void on_parse_from_url(QByteArray data);
};

#endif // SONGKICK_PARSER_H
