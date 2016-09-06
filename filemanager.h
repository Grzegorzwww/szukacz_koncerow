#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QLinkedList>

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <sstream>
using namespace std;
class filemanager : public QObject
{
    Q_OBJECT
public:
    explicit filemanager(QObject *parent = 0);
    void readArtistFromLogFile(const char *nazwapliku, QLinkedList<QString> *artist_list);
    void addArtistToLogFile(const char *nazwapliku, QString *artist_name);

private:

    ofstream fout;
    ifstream fin;
    streampos pos;
    string nazwapliku;

    void openFile(const char *nazwapliku);
    bool fileExists(const char *str);
    QString convertToQString(std::string *str);
    int getLastRecordNumber(string record);


signals:

public slots:
};

#endif // FILEMANAGER_H
