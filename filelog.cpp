#include "filelog.h"


Filelog::Filelog(QWidget *widget) : parent_widget(widget)
{
    qDebug() << "konctruktor";


    file_to_save_log = new QFile();
    file_is_open = false;
    file_was_not_exist = true;

}
Filelog::~Filelog(){

}

void Filelog::on_incoming_settings(stettings_t sett){
    qDebug() << "on_incoming_settings";
    app_stettings = sett;
}

void Filelog::getDefaultSettings( stettings_t app_sett){
    qDebug() <<"getDefaultSettings";
    app_stettings = app_sett;
     qDebug() <<app_stettings.filename;

}

void Filelog::openLogFile(){

    QString file_name = QDir::homePath()+"/Desktop/"+app_stettings.filename;
   file_to_save_log->setFileName( file_name);

   if( file_to_save_log->exists()){
       file_was_not_exist = false;
   }
   else {
       file_was_not_exist = true;
   }
   if(!file_to_save_log->open(QIODevice::ReadWrite | QIODevice::Text  )){
       qDebug() <<"Otwarcie zakończone niepowodzeniem";
       exit(1);
   }
   if(file_to_save_log->exists()){
       file_to_save_log->remove();
       file_to_save_log->close();

       if(!file_to_save_log->open(QIODevice::ReadWrite | QIODevice::Text  )){
           qDebug() <<"Otwarcie zakończone niepowodzeniem";
           exit(1);
       }
   }
}

void Filelog::on_data_to_save_in_file(ArtistToken token){

    int i;
    bool actual_event_was_find = false;

    if(app_stettings.save_in_file == true) {
        if(token.token_type == LASTFM_TOKEN){
            for(i = 0; i < token.occurance_no; i++){
                if(app_stettings.country == POLAND){
                    if(isPolish(token.events_country[i])){
                        generateLASFMEventRecord(i,token);
                    }
                }            else {
                    generateLASFMEventRecord(i,token);
                }
            }
        }
        if(token.token_type == FACEBOOK_TOKEN){
            for(i = 0; i < token.occurance_no; i++){
                if(app_stettings.only_actual == true){
                    if(checkActualDate(token.events_date[i])){
                        if(app_stettings.country == POLAND){
                            if(isPolish(token.events_country[i])){
                                generateFACEBOOKeventRecord(i,token);
                                actual_event_was_find = true;
                                continue;
                            }
                        }else{
                            generateFACEBOOKeventRecord(i,token);
                            actual_event_was_find = true;
                            continue;
                        }
                    }
                }else {
                    if(app_stettings.country == POLAND){
                        if(isPolish(token.events_country[i])){
                            generateFACEBOOKeventRecord(i,token);
                            actual_event_was_find = false;
                        }
                    }
                    else {
                        generateFACEBOOKeventRecord(i,token);
                        actual_event_was_find = false;
                    }
                }
            }
            if(actual_event_was_find != true & app_stettings.only_actual == true){
                on_empty_data_to_save_in_file(token);
            }
        }
    }

}


void Filelog::on_empty_data_to_save_in_file(ArtistToken token){

    QTextStream out(file_to_save_log);
    QString temp_str = "";

    temp_str = temp_str + compensText(token.source.trimmed(), 15, 1);
    temp_str = temp_str + compensText(token.articst_name, 20, 1);
    temp_str = temp_str + compensText("Brak wydarzenia", 30, 1);
    qDebug() << temp_str;
    out << temp_str << "\n";
}



QString Filelog::generateLASFMEventRecord(int no, ArtistToken token){

    QTextStream out(file_to_save_log);
    //out << "Plik z koncertami : " << QDate::currentDate().toString() << "\n\n\n";
    QString temp_str = "LAST.FM: ";
    temp_str = temp_str + compensText(token.articst_name, 20, 1);
    temp_str = temp_str + compensText(token.events_date[no], 30, 1);
    temp_str = temp_str + compensText(token.events_name[no], 50, 1);
    temp_str = temp_str + compensText(token.events_city[no], 30, 1);
    temp_str = temp_str + compensText(token.events_country[no], 30, 1);
    qDebug() << temp_str;
    out << temp_str << "\n";
    return temp_str;

}

QString Filelog::generateFACEBOOKeventRecord(int no, ArtistToken token){

    QTextStream out(file_to_save_log);
    QString temp_str = "FACEBOOK: ";
    temp_str = temp_str + compensText(token.articst_name, 20, 1);
    temp_str = temp_str + compensText(token.events_date[no], 30, 1);
    temp_str = temp_str + compensText(token.events_name[no], 50, 1);
    temp_str = temp_str + compensText(token.events_city[no], 30, 1);
    temp_str = temp_str + compensText(token.events_country[no], 30, 1);
    qDebug() << temp_str;
    out << temp_str << "\n";
    return temp_str;

}



QString Filelog::compensText(QString text, int total_space, int ofset){
    int i;
    QString temp_str = " ";
    if(ofset + text.length() < total_space){
        for(i = 0; i <= total_space; i++){
            if(i == ofset -1){
                temp_str += text;
                i = text.length()+ ofset;
            }
            else temp_str += ' ';
        }
    }
    return temp_str;
}

bool Filelog::isPolish(QString token_country){
    token_country = token_country.trimmed();

    if(token_country.isEmpty())
        return true;

    if((QString::compare(token_country, "Poland", Qt::CaseSensitive) == 0)){
        return true;
    }
    else {
        return false;
    }
}

bool  Filelog::checkActualDate(QString temp_date){

    QDate actual_date(QDate::currentDate());
    QString date_str = temp_date.remove(temp_date.length() - 9, 9);
    actual_date.toString("dd-MM-yyyy");
    QDate event_date = QDate::fromString(date_str , "dd-MM-yyyy");
    if(event_date >=  actual_date){
        return true;
    }
    else
        return false;
}


bool Filelog::generateLogInBackground(){
      QDate actual_date(QDate::currentDate());
      if(app_stettings.generate_log_in_background == true){
          if(QString::compare(app_stettings.first_day.long_day_name, QDate::longDayName(actual_date.dayOfWeek())) == 0 ||
                  QString::compare(app_stettings.second_day.long_day_name, QDate::longDayName(actual_date.dayOfWeek())) == 0){

              QString file_name = QDir::homePath()+"/Desktop/"+app_stettings.filename;
              QFileInfo info(file_name);
              QDateTime file_last_modified =info.lastModified();
              qDebug() << "file_last_modified = "<< file_last_modified.toString("dd-MM-yyyy");
              qDebug() << "actual_date = "<< actual_date.toString("dd-MM-yyyy");
              if(QString::compare(actual_date.toString("dd-MM-yyyy"), file_last_modified.toString("dd-MM-yyyy")) != 0  || file_was_not_exist ){
                  qDebug() <<"mach 2";
                  emit start_download_events(true);
                  return true;

              }else {
                  return true;
              }

          }
      }
      else {
          return false;
      }

}




