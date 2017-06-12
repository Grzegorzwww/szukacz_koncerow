#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QList>
#include <QFile>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <sstream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "defines.h"



//QJsonArray array = { 1, 2.2, QString() };

using namespace std;
class filemanager
{

public:

    explicit filemanager(void );


    void read_artist_list( QList <artist_names_t> &lista_wykonawcow);
    void save_artist_list( QList <artist_names_t> &slista_wykonawcow);



private:

    bool fileExists(QString str);
    QString convertToQString(std::string *str);



signals:

public slots:


};

#endif // FILEMANAGER_H
