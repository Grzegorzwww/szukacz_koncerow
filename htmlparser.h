#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QObject>
#include <string>
#include <event_token.h>
#include <iostream>

using namespace std;
class HTMLParser : public QObject
{
    Q_OBJECT
public:
    explicit HTMLParser(QObject *parent , QString link);



    void parseDataFromHTMLFile(void);
    void getArtistName(QString str);

    QString generateEventRecord(int no);
    int getMaxEventsRecords(void);

private:
    QString data_to_parse;

    ArtistToken *artist_token;


    void saveEventDate(QString *str, long position);
    void saveEventName(QString *str, long position);
    void saveEventCity(QString *str, long position);
    void saveEventCountry(QString *str, long position);

    QString compensText(QString text, int total_space, int ofset);
    void removePolishCharacters(QString *str);


signals:

public slots:
};

#endif // HTMLPARSER_H
