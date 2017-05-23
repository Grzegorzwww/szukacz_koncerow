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
    app_stettings.string_path = QDir::homePath()+"/Desktop";
    app_stettings.filename =  "koncerty.txt";
    app_stettings.first_day.no = 2;
    app_stettings.first_day.long_day_name = "wtorek";
    app_stettings.second_day.no = 5;
    app_stettings.second_day.long_day_name = "piatek";
     app_stettings.generate_log_in_background = false;



//    for(int i = 1; i < 8; i++){
//        ui->comboBox->addItem(QDate::longDayName(i));
//         ui->comboBox_2->addItem(QDate::longDayName(i));
//    }



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
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_send_settings()));



    qDebug() << QStandardPaths::HomeLocation;
    qDebug() << QDir::homePath();


    loadSettings();
    emit send_settings(app_stettings);

}

AppSetting::~AppSetting()
{
    delete ui;
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
;

    settings.endGroup();

//    qDebug() <<  "app_stettings.country" <<  app_stettings.country;
//    qDebug() <<  "app_stettings.highlight" <<  app_stettings.highlight;
//    qDebug() <<  "app_stettings.auto_scroll" <<   app_stettings.auto_scroll;
//    qDebug() <<  "app_stettings.save_in_file" <<  app_stettings.save_in_file;
//    qDebug() <<  "app_stettings.only_actual" <<  app_stettings.only_actual;
//    qDebug() <<  "app_stettings.string_path" <<  app_stettings.string_path;
//    qDebug() <<  "app_stettings.filename" <<  app_stettings.filename;
//    qDebug() <<  "app_stettings.first_day.long_day_name" <<  app_stettings.first_day.long_day_name;
//    qDebug() <<  "app_stettings.first_day.no" <<  app_stettings.first_day.no;
//    qDebug() <<  "app_stettings.second_day.long_day_name" <<  app_stettings.second_day.long_day_name;
//    qDebug() <<  "app_stettings.second_day.no" <<  app_stettings.second_day.no;


 }

 stettings_t  AppSetting::returnDefaultSettings() const {

     return app_stettings;
 }


