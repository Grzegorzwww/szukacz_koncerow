#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileLog = new Filelog(this);
    appEngine = new AppEngine(ui, this);
    graphics  = new Graphics(ui, this);
    appSetting = new AppSetting(this);

    fileLog->getDefaultSettings(appSetting->returnDefaultSettings());
    graphics->getDefaultSettings(appSetting->returnDefaultSettings());

    fileLog->openLogFile();


    connect(this, SIGNAL(enter_pushed_signal()), graphics, SLOT(on_enter_pushed()));
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


    if(fileLog->generateLogInBackground()){
        exit(1);
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_Enter){
         qDebug() << "ENTER";
         emit enter_pushed_signal();
    }

}

void MainWindow::changeEvent(QEvent *event)
{
QMainWindow::changeEvent(event);
    if(event->type() == QEvent::WindowStateChange)
//        if(isMinimized())
//            this->hide();
        ;
}





