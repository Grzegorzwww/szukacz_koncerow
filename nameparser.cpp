#include "nameparser.h"

NameParser::NameParser()
{



}
NameParser::~NameParser() {

}

QString NameParser::generateLastFmLink(QString name){
    QString temp = "https://www.last.fm/music/";
    name.replace(" ", "+");
    name = name+"/+events";
    temp = temp+name;
   // temp = temp.toLower();
     qDebug() <<"lastfm link:"<< temp;
   // temp = "http://www.zmt.tarnow.pl/wordpress/";
    return temp;
}

QString NameParser::generateFacebookLink(QString name){
    QString temp = "https://graph.facebook.com/";
    temp = temp+name;
    temp = temp+"?fields=events,name&access_token="+FB_APP_KEY+"|"+FB_APP_SECRET_KEY;
    //qDebug() << temp;
    return temp;
}



