#ifndef APPENGINE_H
#define APPENGINE_H


#include <QObject>
#include <QDebug>
#include <QString>
#include <QLinkedList>

#include <nameparser.h>
#include <lastfm_parser.h>
#include <event_token.h>
#include <filemanager.h>
#include <fbparser.h>
#include "ui_mainwindow.h"
#include <QMap>
#include <QDate>
#include <QAbstractListModel>
#include <QStandardItem>
#include <QStandardItemModel>



class AppEngine :public filemanager
{
    Q_OBJECT
public:
    explicit AppEngine(Ui::MainWindow *_ui,QObject *parent = 0);

    int actual_tab_set;
    int found_events;
    QObject *my_parent;
    NameParser *name_parser;
    //filemanager *file_manager;
    LASTFMParser *lastfm_parser;
    FBparser *fb_parser;

    Ui::MainWindow *ui;
    ArtistToken *fb_artist_token;



private:


    int progrescounter;
    int find_counter;
    bool search_in_progres;



    void actualizeProgressBar(int artist_last_fm, int artist_facebook);
    bool fillTabResultRecord(ArtistToken *artist_token, QString source);
    bool fillEmptyTabResultRecord(ArtistToken *artist_token, QString source);


signals:

   void lastfm_downloading_finshed(bool);
   void facebook_downloading_finshed(bool);
   void downloading_finshed(bool);
   void add_to_progress_bar(int );
   void add_message_info_label(QString );

   void empty_artist_record(ArtistToken);
   void artist_record(ArtistToken);

public slots:

    void on_start_lastfm_clicked(bool x);

    void on_start_facebook_clicked(bool x);
    void all_test_finished(bool x);

    void on_stop_searching_clicked(bool x);
    void on_reload_artist_list();




};

#endif // APPENGINE_H
