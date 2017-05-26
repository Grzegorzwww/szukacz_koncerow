#include "graphics.h"

Graphics::Graphics(Ui::MainWindow *_ui, QWidget *parent): ui(_ui), my_parent(parent)
{
    ui->tabWidget->setCurrentIndex(0);
    ui->progressBar->setValue(0);
    actual_event_was_find = false;



    _result_table_model = new QStandardItemModel(0,6,this);
    _artist_table_model = new QStandardItemModel(0,2,this);
    actual_date = new QDate(QDate::currentDate());

    remove_from_artist_list = new QAction("Usuń", parent);
    change_artist_fullname = new QAction("Zmień pełną nazwę", parent);
    change_artist_lastfmname = new QAction("Zmien nazwę: last.fm", parent);
    change_artist_facebook = new QAction("Zmień nazwę: facebok.com", parent);
    change_artist_songkick = new QAction("Zmień nazwę: songkick.com", parent);
    find_similas_artist = new QAction("Pokaz podobnych wykonawców", parent);
    show_most_played_with_artists = new QAction("Często występował z:", parent);



    artist_list_menu = new QMenu(parent);
    artist_list_menu->addAction(remove_from_artist_list);
    artist_list_menu->addAction(change_artist_fullname);
    artist_list_menu->addAction(change_artist_lastfmname);
    artist_list_menu->addAction(change_artist_facebook);
    artist_list_menu->addAction(change_artist_songkick);
    artist_list_menu->addAction(find_similas_artist );
    artist_list_menu->addAction(show_most_played_with_artists );




    createTableWidged();

    inicjalice_gui();









    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(on_clear_result_list(bool)));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_dodaj_artist_to_list_clicked(bool)));


    connect(ui->my_lineEdit, SIGNAL(focussed(bool)), this, SLOT(lineEdit_focused(bool)));
    connect(ui->my_lineEdit_2, SIGNAL(focussed(bool)), this, SLOT(lineEdit_2_focused(bool)));
    connect(ui->my_lineEdit_3, SIGNAL(focussed(bool)), this, SLOT(lineEdit_3_focused(bool)));
    connect(ui->my_lineEdit_4, SIGNAL(focussed(bool)), this, SLOT(lineEdit_4_focused(bool)));
    connect(ui->my_lineEdit_5, SIGNAL(focussed(bool)), this, SLOT(lineEdit_5_focused(bool)));


     connect(remove_from_artist_list, SIGNAL(triggered()), this, SLOT(on_remove_artist_from_table_clicked()));
     connect(this, SIGNAL(delete_press()), this, SLOT( on_delete_press()));


    //connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(on_dodaj_facebook_clicked(bool)));
    connect(ui->tabWidget, SIGNAL( currentChanged(int )), this, SLOT(on_main_tab_changed(int)));
   //connect(remove_from_lastfm_list, SIGNAL(triggered()), this, SLOT(on_remove_from_last_fm()));
   // connect(remove_from_facebook_list, SIGNAL(triggered()), this, SLOT(on_remove_from_facebook()));
   // connect(rename_from_lastfm_list, SIGNAL(triggered()), this, SLOT(on_rename_from_last_fm()));
   // connect(rename_from_facebook_list, SIGNAL(triggered()), this, SLOT(on_rename_from_facebook()));
    connect(ui->tableView_3, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_tableView_3_customContextMenuRequested(QPoint)));
    //connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_tableView_2_customContextMenuRequested(QPoint)));

}
Graphics::~Graphics(){

}

void Graphics::inicjalice_gui(){
    ui->my_lineEdit->setText("-");
    ui->my_lineEdit_2->setText("-");
    ui->my_lineEdit_3->setText("-");
    ui->my_lineEdit_4->setText("-");
    ui->my_lineEdit_5->setText("Wpisz...");


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


    _model_items.clear();
    _model_items.append("Wykonawcy ");
    _model_items.append("Nazwa Last.fm ");
    _model_items.append("Nazwa Facebok.com ");
    _model_items.append("Nazwa SongKick.com ");
    _artist_table_model->setHorizontalHeaderLabels(_model_items);
    ui->tableView_3->setModel(_artist_table_model);

    ui->tableView_3->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch);
     ui->tableView_3->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

    ui->tableView_3->horizontalHeader()->resizeSection(0,300);





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
void Graphics::on_clear_artist_table(bool x){
    while( ui->tableView_3->model()->rowCount() > 0 ){
        ui->tableView_3->model()->removeRow(0);
    }
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


void Graphics::on_dodaj_artist_to_list_clicked(bool x){
    artist_names_t temp_artist_token;
    qDebug() << "dodaj clicked";
    temp_artist_token.token_no = 0;
    temp_artist_token.full_name = ui->my_lineEdit->text();
    temp_artist_token.lastfm_name = ui->my_lineEdit_2->text();
    temp_artist_token.fb_name = ui->my_lineEdit_3->text();
    temp_artist_token.songkick_name = ui->my_lineEdit_4->text();
    if(!ui->my_lineEdit->text().compare(ui->my_lineEdit->text(), "-",Qt::CaseInsensitive )){
          QMessageBox::warning(my_parent, tr("Ostrzeżenie"), "Nie podano nazwy wykonawcy");

    }else {
        qDebug() << "ok";
        emit added_artist_clicked(temp_artist_token);
        ui->my_lineEdit->setText("-");
        ui->my_lineEdit_2->setText("-");
        ui->my_lineEdit_3->setText("-");
        ui->my_lineEdit_4->setText("-");
    }
        ui->my_lineEdit->setFocus();
}

void Graphics::on_dodaj_facebook_clicked(bool x){

    //qDebug() << "ZAPISZ PLIK";

   // file_manager->save_artist_list();


//    QString artist_name = ui->lineEdit_5->text();
//    artist_name = artist_name.trimmed();
//    if(!artist_name.isEmpty()){
//        ui->lineEdit_5->clear();
//        addArtistToLogFile("fb_artist_log", &artist_name);
//        ui->label_10->setText("Dodano: "+artist_name);
//        fb_artist_list.clear();
//        readArtistFromLogFile("fb_artist_log", &fb_artist_list);
//        refresh_facebook_artist_tab();
//        ui->progressBar->setMaximum(lastfm_artist_list.size() - 1);
//        // actualizeProgressBar(artist_list.size() , fb_artist_list.size());
//    }
//    else
//        ui->label_4->setText("BLAD: Nie wpisano wykonawcy");
}
void Graphics::on_remove_lastfm_pushed(bool x){

//    lastfm_artist_list.clear();
//    readArtistFromLogFile("artist_log", &lastfm_artist_list);
//    removeArtistFromLogFile("artist_log", 1, &lastfm_artist_list );
//    refresh_artist_list_tab();
}

void Graphics::on_remove_facebook_pushed(bool x){


//    fb_artist_list.clear();
//    readArtistFromLogFile("fb_artist_log", &fb_artist_list);
//    removeArtistFromLogFile("fb_artist_log", 1, &fb_artist_list );
//    refresh_facebook_artist_tab();
}

//void Graphics::on_main_tab_changed(int n){
//    qDebug()<<"on_main_tab_changed " << QString::number(n);
//    if(n == 0){
//        refresh_artist_list_tab();
//    }
//    if(n == 1){
//        refresh_facebook_artist_tab();
//    }
//}

void Graphics::refresh_artist_list_tab(){
    while( ui->tableView_3->model()->rowCount() > 0 ){
        ui->tableView_3->model()->removeRow(0);
    }
//    lastfm_artist_list.clear();
//    readArtistFromLogFile("artist_log", &lastfm_artist_list);
//    readArtistFromLogFile("fb_artist_log", &fb_artist_list);

    QList<QStandardItem *> newRow;
    QList<QString>::iterator i;
//    for (i = lastfm_artist_list.begin(); i != lastfm_artist_list.end(); ++i){
//        newRow.clear();
//        newRow.append(new QStandardItem(*i));
//        newRow.append(new QStandardItem(" - "));
        _artist_table_model->appendRow(newRow);
//    }
    emit reload_list();
}

void Graphics::refresh_facebook_artist_tab(){

//    while( ui->tableView_2->model()->rowCount() > 0 ){
//        ui->tableView_2->model()->removeRow(0);
//    }
//    fb_artist_list.clear();
//    readArtistFromLogFile("fb_artist_log", &fb_artist_list);
    QList<QStandardItem *> newRow;
    QList<QString>::iterator i;
//    for (i = fb_artist_list.begin(); i != fb_artist_list.end(); ++i){
//        newRow.clear();
//        newRow.append(new QStandardItem(*i));
//        newRow.append(new QStandardItem(" - "));
////        _facebook_table_model->appendRow(newRow);
//    }
    emit reload_list();
}

void Graphics::on_remove_from_last_fm(){
    qDebug() << "on_remove_from_last_fm";
    QModelIndexList selection = ui->tableView_3->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        int num = index.row();
//        lastfm_artist_list.clear();
//        readArtistFromLogFile("artist_log", &lastfm_artist_list);
//        if (QMessageBox::question(my_parent, "Czy usunąć?", "Napewno chcesz usunąc wykonawcę:  "+lastfm_artist_list.at(num)+" ?") == QMessageBox::Yes){
//            removeArtistFromLogFile("artist_log", num+1, &lastfm_artist_list );
//        }
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
//    qDebug() <<"on_enter_pushed";
//    if(ui->tabWidget->currentIndex() == 0){
//        on_dodaj_artist_to_list_clicked(true);
//    }else if(ui->tabWidget->currentIndex() == 1){
//        on_dodaj_facebook_clicked(true);
//    }else if(ui->tabWidget->currentIndex() == 2){
//        qDebug() << "Not implemented";
//    }
}

void Graphics::on_tableView_3_customContextMenuRequested(const QPoint &pos)
{
    artist_list_menu->popup(ui->tableView_3->viewport()->mapToGlobal(pos));
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


void Graphics::getArtisListAdress(QList<artist_names_t> *lista){
    lista_wykonawcow = lista;
    on_reflash_artist_list();
}


void Graphics::on_reflash_artist_list(void){
    on_clear_artist_table(true);

    QList<QStandardItem *> newRow;

    if(!lista_wykonawcow->isEmpty()){
         QList<artist_names_t>::iterator i;
        for (i = lista_wykonawcow->begin(); i != lista_wykonawcow->end(); ++i){
            newRow.clear();
            newRow.append(new QStandardItem(i->full_name));
            newRow.append(new QStandardItem(i->lastfm_name));
            newRow.append(new QStandardItem(i->fb_name));
            newRow.append(new QStandardItem(i->songkick_name));
            _artist_table_model->appendRow(newRow);
        }

    }
}
void Graphics::on_remove_artist_from_table_clicked(){
    QModelIndexList selection = ui->tableView_3->selectionModel()->selectedRows();
    int num = -1;
    bool yes_do_not_ask = false;
    bool no_do_not_ask = false;
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        int num = index.row();
        qDebug() << "remove artist number: " << num;
        if(num != -1){
            int ret;
            if(yes_do_not_ask == false && no_do_not_ask == false){
            ret = QMessageBox::question(this, tr("Usunąć ?"),
                                            "Operacja spowoduje bezpowrotne usunięcie wykonawsów z listy:\n"+QString(lista_wykonawcow->at(num).full_name)+"\n"
                                                                                                                                                          "Kontynuowac operacje usuwania ?",
                                            QMessageBox::Yes | QMessageBox::No | QMessageBox::YesAll | QMessageBox::NoAll);
            }
            if(ret == QMessageBox::Yes || yes_do_not_ask == true ){
                emit removed_artist_clicked(num);
            }
            else if(ret == QMessageBox::YesAll ){
                yes_do_not_ask = true;

            }
            else if(ret == QMessageBox::NoAll ){
                no_do_not_ask = true;
                ui->tableView_3->selectionModel()->clearSelection();
                break;
            }
            else if(no_do_not_ask){
                  ui->tableView_3->selectionModel()->select(index, QItemSelectionModel::Deselect);

            }
        }
    }
}

void Graphics::on_delete_press(){
    on_remove_artist_from_table_clicked();
}







