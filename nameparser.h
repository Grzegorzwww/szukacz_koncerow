#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include <QString>
#include <QDebug>

#define FB_APP_KEY "1416908014988033"
#define FB_APP_SECRET_KEY "f1yivkfZWkWN2QXvi8CXj_9Pdwk"



class NameParser
{
public:
    NameParser();
    ~NameParser();

     QString generateLastFmLink(QString name);
     QString generateFacebookLink(QString name);

private:







};

#endif // NAMEPARSER_H
