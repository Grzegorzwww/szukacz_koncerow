#include "appsetting.h"
#include "ui_appsetting.h"

AppSetting::AppSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSetting)
{

    ui->setupUi(this);

    app_stettings.country = 1;
    app_stettings.highlight = false;
    app_stettings.auto_scroll = true;
    app_stettings.save_in_file = true;
    app_stettings.only_actual = true;


    ui->checkBox->setChecked(true);
    ui->checkBox_3->setChecked(false);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(true);

    connect(ui->checkBox, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));
    connect(ui->checkBox_3, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));
    connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));
    connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));
    connect(ui->radioButton_3, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));
    connect(ui->radioButton_4, SIGNAL(clicked(bool)), this, SLOT(on_settings_changed(bool)));



    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(on_about_author(bool)));
//    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_send_settings()));



    qDebug() << QStandardPaths::HomeLocation;
    qDebug() << QDir::homePath();


    loadSettings();
    emit send_settings(app_stettings);

}

AppSetting::~AppSetting()
{
    delete ui;
}

void AppSetting::on_about_author(bool x){
     QMessageBox::information(this, tr("Informacje"), "Nazwa Programu: Szukacz koncertow\nAutor: Grzegorz Warchol\ne-mail: grzegorzw@is.net.pl \nveria: 2");

}

void AppSetting::on_settings_changed(bool x){
    qDebug() << "on_settings_changed";
    //loadSettings();

    if(ui->checkBox_3->isChecked()){
        app_stettings.country = POLAND;
        ui->checkBox->setChecked(false);
    }
    else if(ui->checkBox->isChecked()){
        app_stettings.country = ALL_COUNTRY;
        ui->checkBox_3->setChecked(false);
    }

    if(ui->radioButton->isChecked()){
        app_stettings.highlight = true;
    }else if(ui->radioButton_2->isChecked()){
        app_stettings.highlight = false;
    }

    if(ui->radioButton_3->isChecked()){
        app_stettings.only_actual = true;
    }else if(ui->radioButton_4->isChecked()){
        app_stettings.only_actual = false;
    }

    if(ui->radioButton_5->isChecked()){
        app_stettings.auto_scroll = true;
    }else if(ui->radioButton_6->isChecked()){
        app_stettings.auto_scroll = false;
    }

    saveSettings();


}
 void AppSetting::on_send_settings(){
    on_settings_changed(true);
    emit send_settings(app_stettings);

 }

 void AppSetting::on_load_settings(bool x){

    qDebug() << "on_load_settings";

    loadSettings();



    if(app_stettings.country == POLAND){
        ui->checkBox_3->setChecked(true);
        ui->checkBox->setChecked(false);
    }else if(app_stettings.country == ALL_COUNTRY){
        ui->checkBox->setChecked(true);
        ui->checkBox_3->setChecked(false);
    }

    if(app_stettings.highlight == true){
        ui->radioButton->setChecked(true);
        ui->radioButton_2->setChecked(false);
    }else if(app_stettings.highlight == false){
        ui->radioButton_2->setChecked(true);
        ui->radioButton->setChecked(false);
    }

    if( app_stettings.auto_scroll == true){
        ui->radioButton_5->setChecked(true);
        ui->radioButton_6->setChecked(false);
    }else if(app_stettings.auto_scroll == false){
        ui->radioButton_5->setChecked(false);
        ui->radioButton_6->setChecked(true);
    }

    if(app_stettings.only_actual == true){
        ui->radioButton_3->setChecked(true);
        ui->radioButton_4->setChecked(false);
    }else if(app_stettings.only_actual == false){
        ui->radioButton_3->setChecked(false);
        ui->radioButton_4->setChecked(true);
    }


 }


 void AppSetting::saveSettings(){

     QString m_sSettingsFile = QApplication::applicationDirPath()/*.left(1)*/ + "/settings.ini";
     qDebug() << m_sSettingsFile;
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);    // windows
     settings.beginGroup(SETTINGS_SEARCHING_GROUP);
     settings.setValue(SETTINGS_COUNTRY, app_stettings.country);
     settings.setValue(SETTINGS_COLOUR, app_stettings.highlight);
     settings.setValue(SETTINGS_AUTO_SCROLL, app_stettings.auto_scroll);
     settings.setValue(SETTINGS_ONLY_ACTUAL_DATE, app_stettings.only_actual);

     settings.endGroup();
 }


 void AppSetting::loadSettings(){
    QString m_sSettingsFile = QApplication::applicationDirPath()/*.left(1)*/ + "/settings.ini";
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);    // windows
    settings.beginGroup(SETTINGS_SEARCHING_GROUP);
    app_stettings.country = settings.value(SETTINGS_COUNTRY, 0).toInt();
    app_stettings.highlight = settings.value(SETTINGS_COLOUR, false).toBool();
    app_stettings.auto_scroll = settings.value(SETTINGS_AUTO_SCROLL, true).toBool();
    app_stettings.only_actual = settings.value(SETTINGS_ONLY_ACTUAL_DATE, true).toBool();

    settings.endGroup();


 }

 stettings_t  AppSetting::returnDefaultSettings() const {

     return app_stettings;
 }


