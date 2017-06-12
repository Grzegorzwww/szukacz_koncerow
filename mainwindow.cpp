#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileLog = new Filelog(this);
    graphics  = new Graphics(ui, this);
    appEngine = new AppEngine(ui, this);
    appSetting = new AppSetting(this);
    findArtistDialog = new FindArtistDialog(this);


    graphics->getDefaultSettings(appSetting->returnDefaultSettings());
    graphics->getArtisListAdress(appEngine->returnAtristListAdress());



    connect(graphics, SIGNAL(added_artist_clicked(artist_names_t)), appEngine, SLOT(on_add_artist(artist_names_t)));
    connect(appEngine, SIGNAL(actualize_artist_list()), graphics, SLOT(on_reflash_artist_list()));

    connect(graphics, SIGNAL(removed_artist_clicked(int)), appEngine, SLOT(on_remove_artist(int)));



    connect(graphics, SIGNAL(search_for_last_fm_artist(QString)), appEngine, SLOT(on_start_search_last_fm_artist(QString)));
    connect(graphics, SIGNAL(search_for_facebook_artist(QString)), appEngine, SLOT(on_start_search_facebook_artist(QString)));
    connect(findArtistDialog, SIGNAL(sig_search_for_new_artist_tag()), appEngine, SLOT(on_start_search_facebook_other_tag()) );


    connect(appEngine, SIGNAL(last_fm_artis_find(find_artist_t)), findArtistDialog, SLOT(on_last_fm_artist_find(find_artist_t)));
    connect(appEngine, SIGNAL(facebook_artis_find(find_artist_t)), findArtistDialog, SLOT(on_facebook_artist_find(find_artist_t)));

    connect( findArtistDialog, SIGNAL( artist_was_find(QString)), graphics, SLOT(on_artist_was_find(QString)));
    connect( findArtistDialog, SIGNAL( artist_was_not_find(QString)), graphics, SLOT(on_artist_was_not_find(QString)));

    connect( findArtistDialog, SIGNAL( facebook_artist_was_find(QString)), graphics, SLOT(on_facebook_artist_was_find(QString)));
    connect( findArtistDialog, SIGNAL( facebook_artist_was_not_find(QString)), graphics, SLOT(on_facebook_artist_was_not_find(QString)));



    connect(ui->pushButton_8, SIGNAL(clicked(bool)), appSetting, SLOT(show()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), appSetting, SLOT(on_load_settings(bool)));

   // connect(ui->pushButton, SIGNAL(clicked(bool)), appEngine, SLOT(on_start_lastfm_clicked(bool)));
     connect(ui->pushButton, SIGNAL(clicked(bool)), appEngine, SLOT(on_start_search(bool)));


    connect(ui->pushButton_4, SIGNAL(clicked(bool)), appEngine, SLOT(on_stop_searching_clicked(bool)));

    connect(appEngine, SIGNAL(artist_record(ArtistToken)), graphics, SLOT(on_result_data(ArtistToken)));
    connect(appEngine, SIGNAL(artist_record(ArtistToken)), fileLog, SLOT(  on_data_to_save_in_file(ArtistToken)));
    connect(graphics, SIGNAL(concert_find_counter()), appEngine, SLOT(on_concert_find_counter()));

    connect(appEngine, SIGNAL(empty_artist_record(ArtistToken)), graphics, SLOT(on_empty_result_data(ArtistToken)));
    connect(appEngine, SIGNAL(empty_artist_record(ArtistToken)),  fileLog, SLOT(on_empty_data_to_save_in_file(ArtistToken)));

    connect(appSetting, SIGNAL(send_settings(stettings_t)), graphics, SLOT(on_get_settings(stettings_t)));
    connect(appSetting, SIGNAL(send_settings(stettings_t)), fileLog, SLOT( on_incoming_settings(stettings_t)));

   // connect(graphics, SIGNAL(reload_list()), appEngine, SLOT(on_reload_artist_list()));
    //connect(appEngine, SIGNAL(add_to_progress_bar(int)), ui->progressBar, SLOT(setValue(int)));
    connect(appEngine, SIGNAL(event_searching_finished(int)), ui->progressBar, SLOT(setValue(int)));

    connect(appEngine, SIGNAL(add_message_info_label(QString)), ui->label_3, SLOT(setText(QString)));

    connect(graphics, SIGNAL(search_in_selected_artist_signal(QList<int>)), appEngine, SLOT(on_start_search_only_selected(QList<int>)));


    //connect(fileLog, SIGNAL(start_download_events(bool)), appEngine, SLOT(on_start_lastfm_clicked(bool)));









//    if(fileLog->generateLogInBackground()){
//        exit(1);
//    }



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::changeEvent(QEvent *event)
{
QMainWindow::changeEvent(event);
    if(event->type() == QEvent::WindowStateChange)

        ;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
    case Qt::Key_Return:
    case Qt::Key_Enter:
      qDebug() << "Enter";
      break;
    case Qt::Key_Escape:
      qDebug() << "Escape";
      break;
    case Qt::Key_Insert:
      qDebug() << "Insert";
      break;
    case Qt::Key_Delete:
      qDebug() << "Delete";
      graphics->delete_key_press();
      break;
      default:
      qDebug() << "other" << event->key();
      break;
  }
}




