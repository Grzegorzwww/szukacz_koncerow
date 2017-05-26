#include "filemanager.h"

filemanager::filemanager(void )
{

}


void filemanager::save_artist_list(QList<artist_names_t> &lista_wykonawcow){
    if(!lista_wykonawcow.isEmpty()){
        int index = 0;
        QList<artist_names_t>::iterator i;
        qDebug() << "!lista_wykonawcow.isEmpty()";
        if(fileExists(ARTIST_LOG_NAME)){
            qDebug() << "PLIK ISTNIEJE";
            QFile::remove(ARTIST_LOG_NAME);
        }
            QJsonArray file_struct_array;
            QFile log(ARTIST_LOG_NAME);
            log.open(QIODevice::ReadWrite |  QIODevice::Text);
            QTextStream outStream(&log);
            for (i = lista_wykonawcow.begin(); i != lista_wykonawcow.end(); ++i){
                QJsonObject object;
                QJsonArray tablica = {i->lastfm_name, i->fb_name, i->songkick_name};

                object["index"] = ++index;
                object["artist name"] = i->full_name;
                object["artist_tags"] = tablica;
                file_struct_array << object;

                qDebug() << i->full_name;
            }
            QJsonDocument document(file_struct_array);
            qDebug() << document.toJson(QJsonDocument::Indented);
             outStream << document.toJson(QJsonDocument::Indented);
             log.close();
        }
       qDebug() << "Brak wykonawcow do zapisania";

     }


void filemanager::read_artist_list(QList<artist_names_t> &lista_wykonawcow){

    if(fileExists(ARTIST_LOG_NAME)){

        QFile log(ARTIST_LOG_NAME);
        if(!log.open(QIODevice::ReadOnly |  QIODevice::Text)){
            qDebug() << log.errorString();
        }else{
            lista_wykonawcow.clear();
            artist_names_t temp_artist;

            QJsonDocument document = QJsonDocument::fromJson(log.readAll());

          QJsonArray file_struct_array = document.array();

            //QJsonArray file_struct_array(document);
            QJsonObject event_obj;

            foreach(const QJsonValue &value, file_struct_array ){
                event_obj = value.toObject();

                temp_artist.token_no = event_obj["index"].toInt();
                temp_artist.full_name = event_obj["artist name"].toString();
                QJsonArray artist_tags = event_obj["artist_tags"].toArray();
                temp_artist.songkick_name = artist_tags[2].toString();
                temp_artist.fb_name = artist_tags[1].toString();
                temp_artist.lastfm_name = artist_tags[1].toString();



                lista_wykonawcow.append(temp_artist);
            }
        }
    }

     QList<artist_names_t>::iterator i;
       for (i = lista_wykonawcow.begin(); i != lista_wykonawcow.end(); ++i){
           qDebug() << "i->token_no;" << i->token_no;
           qDebug() << "i->full_name;" << i->full_name;
           qDebug() << "i->lastfm_name" << i->lastfm_name;
           qDebug() << "i->fb_name" << i->fb_name;
           qDebug() << "i->songkick_name" << i->songkick_name;
       }
}



bool filemanager::fileExists(QString str)
{
    QFile Fout(str);
    if(Fout.exists()){
        return true;
    }
    else {

        return false;
    }
   Fout.close();

}


QString filemanager::convertToQString(std::string *str){
    int i;
    QString temp_str;
    bool flag = false;
    for(i = 0; i < str->length(); i++){
        if(str->at(i) != ' ' && flag == false){
            continue;
        }else if(str->at(i) == ' ' && flag == false){
            flag = true;
            continue;
        }
        else
            temp_str.append(str->at(i));
    }
    return temp_str;
}





