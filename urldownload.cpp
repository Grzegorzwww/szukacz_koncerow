#include "urldownload.h"

URLDownload::URLDownload(QObject *parent) : QObject(parent)
{


    m_netwManager = new QNetworkAccessManager(this);
    connect(m_netwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished(QNetworkReply*)));
}

URLDownload::~URLDownload()
{
    delete m_netwManager;


}

void URLDownload::download_data_from_url(QString link){
    QUrl Url(link);
    QNetworkRequest request(Url);
    m_netwManager->get(request);
}



void URLDownload::slot_netwManagerFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }

    qDebug() << "ContentType:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();
    received_data = reply->readAll();
    emit data_recieved(received_data);

}

