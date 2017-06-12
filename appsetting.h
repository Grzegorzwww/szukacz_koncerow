#ifndef APPSETTING_H
#define APPSETTING_H

#include <QDialog>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <string>
#include <map>
#include <QMap>
#include <QDir>
#include <QApplication>
#include <QStandardPaths>
#include <QMessageBox>

static const QString SETTINGS_ORG = "szukacz_koncertow";
static const QString  SETTINGS_APP_NAME = "szukacz koncertow";
static const QString  SETTINGS_SEARCHING_GROUP = "searching_settings_group";

static const QString SETTINGS_COUNTRY= "country";
static const QString SETTINGS_COLOUR = "color_record";
static const QString SETTINGS_AUTO_SCROLL = "auto_scroll_to_botton";
static const QString SETTINGS_SAVE_IN_FILE = "save_in_file";
static const QString SETTINGS_ONLY_ACTUAL_DATE = "only_actual_date";
static const QString SETTINGS_PATH_TO_SAVE_FILE = "path_to_file";
static const QString SETTINGS_FILE_NAME = "filename";
static const QString SETTINGS_FIRST_DAY = "first_day_to_check";
static const QString SETTINGS_FIRST_DAY_NO = "first_day_to_check_no";
static const QString SETTINGS_SECOND_DAY = "second_day_to_check";
static const QString SETTINGS_SECOND_DAY_NO = "second_day_to_check_no";
static const QString SETTINGS_GENERATE_LOG = "generate_log_in_background";



static const int ALL_COUNTRY = 0;
static const int POLAND = 1;

typedef struct date_s {
    int no;
    QString long_day_name;
} date_t;

typedef struct stettings_s{
    int country;
    bool highlight;
    bool auto_scroll;
    bool save_in_file;
    bool only_actual;
    QString string_path;
    QString filename;
    date_t first_day;
    date_t second_day;
    bool generate_log_in_background;

} stettings_t;



namespace Ui {
class AppSetting;
}

class AppSetting : public QDialog
{
    Q_OBJECT

public:
    explicit AppSetting(QWidget *parent = 0);
    ~AppSetting();

     stettings_t  returnDefaultSettings() const ;

private:

    Ui::AppSetting *ui;
    stettings_t app_stettings;

    void saveSettings();
    void loadSettings();
    void reateWeek();


public slots:
    void on_settings_changed(bool x);
    void on_about_author(bool x);
    void on_send_settings();
    void on_load_settings(bool x);

private slots:

signals:

    void send_settings(stettings_t);

};

#endif // APPSETTING_H
