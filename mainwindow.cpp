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


    graphics->getDefaultSettings(appSetting->returnDefaultSettings());
    graphics->getArtisListAdress(appEngine->returnAtristListAdress());



    connect(graphics, SIGNAL(added_artist_clicked(artist_names_t)), appEngine, SLOT(on_add_artist(artist_names_t)));
    connect(appEngine, SIGNAL(actualice_artist_list()), graphics, SLOT(on_reflash_artist_list()));

    connect(graphics, SIGNAL(removed_artist_clicked(int)), appEngine, SLOT(on_remove_artist(int)));








    connect(ui->pushButton_8, SIGNAL(clicked(bool)), appSetting, SLOT(show()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), appSetting, SLOT(on_load_settings(bool)));

    connect(ui->pushButton, SIGNAL(clicked(bool)), appEngine, SLOT(on_start_lastfm_clicked(bool)));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), appEngine, SLOT(on_stop_searching_clicked(bool)));

    connect(appEngine, SIGNAL(artist_record(ArtistToken)), graphics, SLOT(on_result_data(ArtistToken)));
    connect(appEngine, SIGNAL(artist_record(ArtistToken)), fileLog, SLOT(  on_data_to_save_in_file(ArtistToken)));

    connect(appEngine, SIGNAL(empty_artist_record(ArtistToken)), graphics, SLOT(on_empty_result_data(ArtistToken)));
    connect(appEngine, SIGNAL(empty_artist_record(ArtistToken)),  fileLog, SLOT(on_empty_data_to_save_in_file(ArtistToken)));


    connect(appSetting, SIGNAL(send_settings(stettings_t)), graphics, SLOT(on_get_settings(stettings_t)));
    connect(appSetting, SIGNAL(send_settings(stettings_t)), fileLog, SLOT( on_incoming_settings(stettings_t)));

    connect(graphics, SIGNAL(reload_list()), appEngine, SLOT(on_reload_artist_list()));
    connect(appEngine, SIGNAL(add_to_progress_bar(int)), ui->progressBar, SLOT(setValue(int)));
    connect(appEngine, SIGNAL(add_message_info_label(QString)), ui->label_3, SLOT(setText(QString)));

    connect(fileLog, SIGNAL(start_download_events(bool)), appEngine, SLOT(on_start_lastfm_clicked(bool)));









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




