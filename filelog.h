#ifndef FILELOG_H
#define FILELOG_H
#include <QDebug>
#include <QWidget>
#include <QFile>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <event_token.h>
#include <appsetting.h>
#include <QFileInfo>
#include <QWidget>


class Filelog : public QWidget
{
Q_OBJECT

public:
    explicit Filelog(QWidget *widget = 0);
    ~Filelog();
    void getDefaultSettings( stettings_t app_sett);

    bool generateLogInBackground();
     void openLogFile();

private:
    stettings_t app_stettings;
    QWidget *parent_widget;
    QFile *file_to_save_log;
    bool file_is_open;
    bool file_was_not_exist;



    QString compensText(QString text, int total_space, int ofset);
    QString generateLASFMEventRecord(int no, ArtistToken token);
    QString generateFACEBOOKeventRecord(int no, ArtistToken token);
    bool checkActualDate(QString temp_date);
    bool isPolish(QString token_country);



public slots:

    void on_incoming_settings(stettings_t sett);
    void on_data_to_save_in_file(ArtistToken token);
    void on_empty_data_to_save_in_file(ArtistToken token);

signals:

    void start_download_events(bool x);

};

#endif // FILELOG_H
