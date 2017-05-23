#include "graphics.h"

Graphics::Graphics(Ui::MainWindow *_ui, QWidget *parent): ui(_ui), my_parent(parent)
{
    ui->tabWidget->setCurrentIndex(1);
    ui->progressBar->setValue(0);
    actual_event_was_find = false;


    _result_table_model = new QStandardItemModel(0,6,this);
   // _facebook_table_model = new QStandardItemModel(0,2,this);
    _artist_table_model = new QStandardItemModel(0,2,this);
    actual_date = new QDate(QDate::currentDate());

    remove_from_lastfm_list = new QAction("Usuń z listy", parent);
    remove_from_facebook_list = new QAction("Usuń z listy",parent);
    rename_from_lastfm_list = new QAction("Zmien nazwę ",parent);
    rename_from_facebook_list = new QAction("Zmien nazwę ",parent);

    lastfm_list_menu = new QMenu(parent);
    facebook_list_menu= new QMenu(parent);
    lastfm_list_menu->addAction(remove_from_lastfm_list);
    lastfm_list_menu->addAction(rename_from_lastfm_list);
    facebook_list_menu->addAction(remove_from_facebook_list);
    facebook_list_menu->addAction(rename_from_facebook_list);


    createTableWidged();
    refresh_artist_list_tab();
    refresh_facebook_artist_tab();

    actualizeProgressBar(lastfm_artist_list.size() , fb_artist_list.size());

    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(on_clear_result_list(bool)));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_dodaj_lastfm_clicked(bool)));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(on_dodaj_facebook_clicked(bool)));
    connect(ui->tabWidget, SIGNAL( currentChanged(int )), this, SLOT(on_main_tab_changed(int)));
    connect(remove_from_lastfm_list, SIGNAL(triggered()), this, SLOT(on_remove_from_last_fm()));
    connect(remove_from_facebook_list, SIGNAL(triggered()), this, SLOT(on_remove_from_facebook()));
    connect(rename_from_lastfm_list, SIGNAL(triggered()), this, SLOT(on_rename_from_last_fm()));
    connect(rename_from_facebook_list, SIGNAL(triggered()), this, SLOT(on_rename_from_facebook()));
    connect(ui->tableView_3, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_tableView_3_customContextMenuRequested(QPoint)));
    //connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_tableView_2_customContextMenuRequested(QPoint)));

}
Graphics::~Graphics(){

}

void  Graphics::createTableWidged(){
    QStringList _model_items;

    _model_items.append("Żródło");
    _model_items.append("Nazwa wykonawcy");
    _model_items.append("Nazwa wydarzenia");
    _model_items.append("Data");
    _model_items.append("Miasto");
    _model_items.append("Państwo");
    _result_table_model->setHorizontalHeaderLabels(_model_items);

    ui->tableView->setModel(_result_table_model);

    ui->tableView->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->resizeSection(0, 80);

//    _model_items.clear();
//    _model_items.append("Wykonawcy ");
//    _model_items.append("Dodatkowe infomacje ");
//    _facebook_table_model->setHorizontalHeaderLabels(_model_items);
//    ui->tableView_2->setModel(_facebook_table_model);
//    ui->tableView_2->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch);
//    ui->tableView_2->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Fixed);
//    ui->tableView_2->horizontalHeader()->resizeSection(1, 200);


    _model_items.clear();
    _model_items.append("Wykonawcy ");
    _model_items.append("Nazwa Last.fm ");
    _model_items.append("Nazwa Facebok.com ");
    _model_items.append("Nazwa SongKick.com ");
    _artist_table_model->setHorizontalHeaderLabels(_model_items);
    ui->tableView_3->setModel(_artist_table_model);

    ui->tableView_3->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Fixed);
    ui->tableView_3->horizontalHeader()->resizeSection(0,300);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Fixed);
     ui->tableView_3->horizontalHeader()->resizeSection(1,158);
     ui->tableView_3->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Fixed);
     ui->tableView_3->horizontalHeader()->resizeSection(2,158);
      ui->tableView_3->horizontalHeader()->setSectionResizeMode( 3, QHeaderView::Fixed);
       ui->tableView_3->horizontalHeader()->resizeSection(3,158);


}
void Graphics::fillRecord(int no, ArtistToken token){
    QList<QStandardItem *> newRow;
    newRow.clear();
    newRow.append(new QStandardItem(token.source.trimmed()));
    newRow.append(new QStandardItem(token.articst_name.trimmed()));
    newRow.append(new QStandardItem(token.events_name[no].trimmed()));
    newRow.append(new QStandardItem(token.events_date[no].trimmed()));
    newRow.append(new QStandardItem(token.events_city[no].trimmed()));
    newRow.append(new QStandardItem(token.events_country[no].trimmed()));
    _result_table_model->appendRow(newRow);
}

void Graphics::on_result_data(ArtistToken token){
    int i;

    actual_event_was_find = false;

    if(token.token_type == LASTFM_TOKEN){
        for(i = 0; i < token.occurance_no; i++){
            if(app_stettings.country == POLAND){
                  if(isPolish(token.events_country[i])){
                       fillRecord(i,token);
                  }
            }
            else {
                   fillRecord(i,token);
            }
        }
    }
    else if(token.token_type == FACEBOOK_TOKEN){
        for(i = 0; i < token.occurance_no; i++){
            if(app_stettings.only_actual == true){
                if(checkActualDate(token.events_date[i])){
                    if(app_stettings.country == POLAND){
                        if(isPolish(token.events_country[i])){
                            fillRecord(i,token);
                            actual_event_was_find = true;
                            continue;
                        }
                    }else{
                        fillRecord(i,token);
                        actual_event_was_find = true;
                        continue;
                    }
                }
            }else {
                if(app_stettings.country == POLAND){
                    if(isPolish(token.events_country[i])){
                        fillRecord(i,token);
                        actual_event_was_find = false;
                    }
                }
                else {
                    fillRecord(i,token);
                    actual_event_was_find = false;
                }
            }
        }
        if(actual_event_was_find != true & app_stettings.only_actual == true){
            on_empty_result_data(token);
        }
    }
    if(app_stettings.auto_scroll == true){
        ui->tableView->scrollToBottom();
    }

}


void Graphics::on_empty_result_data(ArtistToken token){

    QList<QStandardItem *> newRow;
    newRow.clear();
    newRow.append(new QStandardItem(token.source.trimmed()));
    newRow.append(new QStandardItem(token.articst_name.trimmed()));
    newRow.append(new QStandardItem("Brak Wydarzenia"));
    newRow.append(new QStandardItem("-"));
    newRow.append(new QStandardItem("-"));
    newRow.append(new QStandardItem("-"));
    _result_table_model->appendRow(newRow);

}

void Graphics::on_clear_result_list(bool x){
    while( ui->tableView->model()->rowCount() > 0 ){
        ui->tableView->model()->removeRow(0);
    }
    ui->progressBar->setValue(ui->tableView->model()->rowCount());
    ui->label_3->setText("lista wyczyszczona");
}

bool  Graphics::checkActualDate(QString temp_date){

    QString date_str = temp_date.remove(temp_date.length() - 9, 9);
    actual_date->toString("dd-MM-yyyy");
    QDate event_date = QDate::fromString(date_str , "dd-MM-yyyy");
    if(event_date >=  *actual_date){
        return true;
    }
    else
        return false;
}
void  Graphics::on_get_settings(stettings_t set){
    qDebug() << "on_get_settings";
    app_stettings = set;
}

void Graphics::on_dodaj_lastfm_clicked(bool x){
    QString artist_name = ui->lineEdit->text();
    artist_name = artist_name.trimmed();
    if(!artist_name.isEmpty()){
        ui->lineEdit->clear();
        addArtistToLogFile("artist_log", &artist_name);
        ui->label_4->setText("Dodano: "+artist_name);
        lastfm_artist_list.clear();
        readArtistFromLogFile("artist_log", &lastfm_artist_list);
        refresh_artist_list_tab();
        //actualizeProgressBar(artist_list.size() , fb_artist_list.size());
    }
    else
        ui->label_4->setText("BLAD: Nie wpisano wykonawcy");
}

void Graphics::on_dodaj_facebook_clicked(bool x){
    QString artist_name = ui->lineEdit_5->text();
    artist_name = artist_name.trimmed();
    if(!artist_name.isEmpty()){
        ui->lineEdit_5->clear();
        addArtistToLogFile("fb_artist_log", &artist_name);
        ui->label_10->setText("Dodano: "+artist_name);
        fb_artist_list.clear();
        readArtistFromLogFile("fb_artist_log", &fb_artist_list);
        refresh_facebook_artist_tab();
        ui->progressBar->setMaximum(lastfm_artist_list.size() - 1);
        // actualizeProgressBar(artist_list.size() , fb_artist_list.size());
    }
    else
        ui->label_4->setText("BLAD: Nie wpisano wykonawcy");
}
void Graphics::on_remove_lastfm_pushed(bool x){

    lastfm_artist_list.clear();
    readArtistFromLogFile("artist_log", &lastfm_artist_list);
    removeArtistFromLogFile("artist_log", 1, &lastfm_artist_list );
    refresh_artist_list_tab();
}

void Graphics::on_remove_facebook_pushed(bool x){


    fb_artist_list.clear();
    readArtistFromLogFile("fb_artist_log", &fb_artist_list);
    removeArtistFromLogFile("fb_artist_log", 1, &fb_artist_list );
    refresh_facebook_artist_tab();
}

void Graphics::on_main_tab_changed(int n){
    qDebug()<<"on_main_tab_changed " << QString::number(n);
    if(n == 0){
        refresh_artist_list_tab();
    }
    if(n == 1){
        refresh_facebook_artist_tab();
    }
}

void Graphics::refresh_artist_list_tab(){
    while( ui->tableView_3->model()->rowCount() > 0 ){
        ui->tableView_3->model()->removeRow(0);
    }
    lastfm_artist_list.clear();
    readArtistFromLogFile("artist_log", &lastfm_artist_list);
    readArtistFromLogFile("fb_artist_log", &fb_artist_list);

    QList<QStandardItem *> newRow;
    QList<QString>::iterator i;
    for (i = lastfm_artist_list.begin(); i != lastfm_artist_list.end(); ++i){
        newRow.clear();
        newRow.append(new QStandardItem(*i));
        newRow.append(new QStandardItem(" - "));
        _artist_table_model->appendRow(newRow);
    }
    emit reload_list();
}

void Graphics::refresh_facebook_artist_tab(){

//    while( ui->tableView_2->model()->rowCount() > 0 ){
//        ui->tableView_2->model()->removeRow(0);
//    }
    fb_artist_list.clear();
    readArtistFromLogFile("fb_artist_log", &fb_artist_list);
    QList<QStandardItem *> newRow;
    QList<QString>::iterator i;
    for (i = fb_artist_list.begin(); i != fb_artist_list.end(); ++i){
        newRow.clear();
        newRow.append(new QStandardItem(*i));
        newRow.append(new QStandardItem(" - "));
//        _facebook_table_model->appendRow(newRow);
    }
    emit reload_list();
}

void Graphics::on_remove_from_last_fm(){
    qDebug() << "on_remove_from_last_fm";
    QModelIndexList selection = ui->tableView_3->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        int num = index.row();
        lastfm_artist_list.clear();
        readArtistFromLogFile("artist_log", &lastfm_artist_list);
        if (QMessageBox::question(my_parent, "Czy usunąć?", "Napewno chcesz usunąc wykonawcę:  "+lastfm_artist_list.at(num)+" ?") == QMessageBox::Yes){
            removeArtistFromLogFile("artist_log", num+1, &lastfm_artist_list );
        }
        refresh_artist_list_tab();
    }
}

void Graphics::on_remove_from_facebook(){
    qDebug() << "on_remove_from_facebook";
    //QModelIndexList selection = ui->tableView_2->selectionModel()->selectedRows();
//    for(int i=0; i< selection.count(); i++)
//    {
//        QModelIndex index = selection.at(i);
//        int num = index.row();
//        fb_artist_list.clear();
//        readArtistFromLogFile("fb_artist_log", &fb_artist_list);
//        if (QMessageBox::question(my_parent, "Czy usunąć?", "Napewno chcesz usunąc wykonawcę:  "+fb_artist_list.at(num)+" ?") == QMessageBox::Yes){
//            removeArtistFromLogFile("fb_artist_log", num+1, &fb_artist_list );
//        }
//        refresh_facebook_artist_tab();
//    }
}
void Graphics::on_rename_from_last_fm(){


}
void Graphics::on_rename_from_facebook(){

}

void Graphics::on_enter_pushed(){
    qDebug() <<"on_enter_pushed";
    if(ui->tabWidget->currentIndex() == 0){
        on_dodaj_lastfm_clicked(true);
    }else if(ui->tabWidget->currentIndex() == 1){
        on_dodaj_facebook_clicked(true);
    }else if(ui->tabWidget->currentIndex() == 2){
        qDebug() << "Not implemented";
    }
}

void Graphics::on_tableView_3_customContextMenuRequested(const QPoint &pos)
{
    lastfm_list_menu->popup(ui->tableView_3->viewport()->mapToGlobal(pos));
}
void Graphics::on_tableView_2_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "on_tableView_2_customContextMenuRequested";
   // facebook_list_menu->popup(ui->tableView_2->viewport()->mapToGlobal(pos));
}
void Graphics::actualizeProgressBar(int artist_last_fm, int artist_facebook){
    ui->progressBar->setMaximum((artist_last_fm - 1) + (artist_facebook - 1)  );
}

bool Graphics::isPolish(QString token_country){
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

void Graphics::getDefaultSettings( stettings_t app_sett){
    qDebug() << "getDefaultSettings";
    app_stettings = app_sett;
}
