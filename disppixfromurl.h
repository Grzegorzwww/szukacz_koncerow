#ifndef DISPPIXFROMURL_H
#define DISPPIXFROMURL_H

#include <iostream>
#include <urldownload.h>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QByteArray>
class DISPPixFromUrl : public QObject
{
    Q_OBJECT
public:
    explicit DISPPixFromUrl(QObject *parent = 0);
    ~DISPPixFromUrl();


    void displayPic(QLabel *label, QString url);

private:

    URLDownload *url_downlaod;
    QLabel *label_to_disp;

signals:

    picture_complete_received(QPixmap);

public slots:


    void on_pic_data_received(QByteArray data);
};

#endif // DISPPIXFROMURL_H
