#include "nameparser.h"

NameParser::NameParser()
{



}
NameParser::~NameParser() {

}

QString NameParser::generateLink(QString name){
    QString temp = "http://www.last.fm/music/";
    name.replace(" ", "+");
    name = name+"/+events";
    temp = temp+name;
   // temp = temp.toLower();
    // qDebug() << temp;
    return temp;
}

