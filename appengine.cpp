#include "appengine.h"
#include "ui_mainwindow.h"

AppEngine::AppEngine(Ui::MainWindow *_ui, QObject *parent):
    ui(_ui)
{
    qDebug() << "AppEngine";
    ui->tabWidget->setCurrentIndex(2);
    actual_tab_set = 2;
    found_events = 0;
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->radioButton_2->setChecked(true);


    name_parser  = new NameParser();
    file_manager = new filemanager();
    my_parent = new QObject(parent);


    file_manager->readArtistFromLogFile("artist_log", &artist_list);
    ui->progressBar->setMaximum(artist_list.size() - 1);



    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_dodaj_clicked(bool)));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(on_start_clicked(bool)));
    connect(ui->tabWidget, SIGNAL( currentChanged(int )), this, SLOT(on_main_tab_changed(int)));

}


void AppEngine::on_dodaj_clicked(bool x){

    qDebug() << "on_dodaj_clicked"<<x;
    QString artist_name = ui->lineEdit->text();
    if(!artist_name.isEmpty()){
        ui->lineEdit->clear();
        file_manager->addArtistToLogFile("artist_log", &artist_name);
        ui->label_4->setText("Dodano: "+artist_name);
        artist_list.clear();
        file_manager->readArtistFromLogFile("artist_log", &artist_list);
        ui->progressBar->setMaximum(artist_list.size() - 1);
    }
    else
        ui->label_4->setText("BLAD: Nie wpisano wykonawcy");




}

void AppEngine::on_start_clicked(bool x){
    ui->tabWidget->setCurrentIndex(2);

    QLinkedList<QString>::iterator i;
    int j = 0;
    ui->textBrowser->clear();
    for (i = artist_list.begin(); i != artist_list.end(); ++i){
        qDebug() << *i << endl;
        QString artist_name = *i;
        ui->label_3->setText(artist_name);
        ui->progressBar->setValue(j++);

        html_parser  = new HTMLParser( my_parent, name_parser->generateLink(artist_name ));
        html_parser->getArtistName(artist_name );
        html_parser->parseDataFromHTMLFile();

        int i;
        if(html_parser->getMaxEventsRecords() == 0){
            if(ui->radioButton->isChecked()){
                QString temp_str = "<font color=\"red\">"+html_parser->generateEventRecord(i)+"</font>";
                ui->textBrowser->append(temp_str);
            }else {
                ui->textBrowser->append(html_parser->generateEventRecord(i));
            }


        }
        for(i = 0; i < html_parser->getMaxEventsRecords(); i++){
            found_events++;
            if(ui->radioButton->isChecked()){
                QString temp_str = "<font color=\"green\">"+html_parser->generateEventRecord(i)+"</font>";
                ui->textBrowser->append(temp_str);
            }else {
                ui->textBrowser->append(html_parser->generateEventRecord(i));
            }
        }
        delete  html_parser;
    }
    ui->label_3->setText("Dla podanych wykonawcow znaleziono: "+QString::number( found_events)+" koncerty.");
}

void AppEngine::on_main_tab_changed(int n){
    actual_tab_set = n;
    if(n = 1){
        artist_list.clear();
        file_manager->readArtistFromLogFile("artist_log", &artist_list);
        QLinkedList<QString>::iterator i;
        int j = 1;
         ui->textBrowser_2->clear();
        for (i = artist_list.begin(); i != artist_list.end(); ++i){
             ui->textBrowser_2->append(QString::number(j)+". "+*i);
             j++;
        }


    }
}
 void AppEngine::on_enter_pushed(void){
     if(actual_tab_set == 1){
         on_dodaj_clicked(true);
     }

 }



