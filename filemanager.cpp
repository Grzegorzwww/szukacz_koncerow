#include "filemanager.h"

filemanager::filemanager(QObject *parent) : QObject(parent)
{



}
void filemanager::openFile(const char *nazwapliku)
{
    fout.open(nazwapliku,  ios_base::app |  ios_base::ate);
}


bool filemanager::fileExists(const char *str)
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
void filemanager::readArtistFromLogFile(const char *nazwapliku, QList <QString> *artist_list){
        char ch;
        std::string wiersz;
        if(fileExists(nazwapliku)){
            fin.open(nazwapliku);

            while(std::getline(  fin, wiersz )){
             artist_list->append(convertToQString(&wiersz));
             //std::cout << wiersz << std::endl;
            }
    fin.close();
    }else {
        qDebug() <<QString::fromUtf8(nazwapliku) << "plik nie istnieje, nie dodano zadnego wykonawcy";
    }
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
int filemanager::getLastRecordNumber(string record){


     std::locale loc;
      if (isdigit(record[0],loc))
      {
        int num;
        std::stringstream(record) >> num;
        return num;
      }
      else return -1;

}

void filemanager::addArtistToLogFile(const char *nazwapliku, QString *artist_name){
    int last_artist_num = 0;
    if(fileExists(nazwapliku)){
         fin.open(nazwapliku);
        std::string wiersz;
          while( std::getline( fin, wiersz ) ){
               ;
          }
         last_artist_num = getLastRecordNumber(wiersz);
         qDebug() << QString::number(last_artist_num);
         fin.close();
         fout.open(nazwapliku, ios_base::app |  ios_base::ate);
         if(  fout.good() )
            {
                fout.seekp(0,std::ios_base::end);
                fout << endl;
                fout << ++last_artist_num <<". "<< artist_name->toStdString();
                fout.close();
            }
    }
    else {
        fout.open(nazwapliku, ios_base::app |  ios_base::ate);
        if(  fout.good() )
           {
               fout.seekp(0,std::ios_base::end);
               fout << ++last_artist_num <<". "<< artist_name->toStdString();
               fout.close();
           }

    }
}

void filemanager::removeArtistFromLogFile(const char *nazwapliku, int num, QList<QString> *_list){

    QList<QString>::iterator i;
    QString temp_str;
    qDebug() << num;

    if(num > 0 && num <= _list->size()){

        fout.open(nazwapliku,  std::ofstream::out | std::ofstream::trunc);
        fout.seekp(0,std::ios_base::beg);

        int j;
        for (j = 0, i = _list->begin(); j < _list->size(),  i != _list->end(); j++, ++i){
            temp_str = *i;
            if( j+1 == num){
                qDebug() << "Usunieto "<<  temp_str;
                //msg_label->setText("Usunieto: "+ temp_str);
                continue;
            }else {
                fout <<j+1<<". "<< temp_str.toStdString() ;
                if(j != _list->size() -2){
                    fout << endl;
                }
            }
        }
        fout.close();
    } else {

    }


}
/*
ostream & operator<<(ostream &os, filemanager &in){

     os << in.str;
     return os;
}*/




