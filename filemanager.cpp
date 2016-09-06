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
    ifstream plik(str);
    bool to_return = plik;
    plik.close();
    return to_return;
}
void filemanager::readArtistFromLogFile(const char *nazwapliku, QLinkedList <QString> *artist_list){
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
        qDebug() <<"plik nie istnieje, nie dodano zadnego wykonawcy";
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



