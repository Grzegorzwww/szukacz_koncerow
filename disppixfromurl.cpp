#include "disppixfromurl.h"

DISPPixFromUrl::DISPPixFromUrl(QObject *parent) : QObject(parent)
{

    url_downlaod = new URLDownload(this);




    connect(url_downlaod, SIGNAL(data_recieved(QByteArray)), this, SLOT(on_pic_data_received(QByteArray)));


}


DISPPixFromUrl::~DISPPixFromUrl(){

    delete url_downlaod;
}




void DISPPixFromUrl::on_pic_data_received(QByteArray data){

    QPixmap temp_pic;
    temp_pic.loadFromData(data);
    label_to_disp->setPixmap(temp_pic);
    emit  picture_complete_received(temp_pic);
}


void DISPPixFromUrl::displayPic(QLabel *label, QString url){
    label_to_disp = label;
    if(!url.isEmpty()){
        url_downlaod->download_data_from_url(url);
    }
}
