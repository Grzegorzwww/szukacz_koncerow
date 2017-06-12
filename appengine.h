#ifndef APPENGINE_H
#define APPENGINE_H


#include <QObject>
#include <QDebug>
#include <QString>
#include <QLinkedList>
#include "gw_class.h"

#include <nameparser.h>
#include "search_artist.h"
#include <lastfm_parser.h>
#include <event_token.h>
#include <filemanager.h>
#include <fbparser.h>
#include "ui_mainwindow.h"
#include "songkick_parser.h"
#include <QMap>
#include <QDate>
#include <QRegExp>
#include <QAbstractListModel>
#include <QStandardItem>
#include <QStandardItemModel>




class AppEngine :public QObject/*:public filemanager*/
{
    Q_OBJECT
public:
    explicit AppEngine(Ui::MainWindow *_ui,QObject *parent = 0);

    int actual_tab_set;
    int found_events;
    QObject *my_parent;
    NameParser *name_parser;
    LASTFMParser *lastfm_parser;
    FBparser *fb_parser;
    SONGKICKparser *songkick_parser;

    Ui::MainWindow *ui;
    ArtistToken *fb_artist_token;

    // gw_automatic_vector<QString> fb_search_suffix_list;
     //std::vector <QString> fb_search_suffix_list;

    QString suffix_to_search[3];
    int suffix_to_search_state;




    QList <artist_names_t> lista_wykonawcow;

    filemanager *file_manager;
    search_artist *search_for_artist;


     QList <artist_names_t>*  returnAtristListAdress();


private:


    int progrescounter;
    int find_counter;
    bool search_in_progres;

    QString actual_searching_artist_name;
    QList<QString> fb_artist_token_suffix;


    void actualizeProgressBar(int artist_last_fm, int artist_facebook);
    bool fillTabResultRecord(ArtistToken *artist_token, QString source);
    bool fillEmptyTabResultRecord(ArtistToken *artist_token, QString source);



public slots:

    void on_start_search_last_fm_artist(QString artist_name);
     void on_start_search_facebook_artist(QString artist_name);
     void on_start_search_only_selected(QList<int> list_to_display);
     void on_start_search_facebook_other_tag();




    bool on_parse_lastfm_artist(QString artist_tag);

    bool on_parse_facebook_artist(QString tag, QString pre_tag);
    void all_test_finished(bool x);

    void on_stop_searching_clicked(bool x);
    void on_start_search(bool);


    void on_add_artist(artist_names_t token);
    void on_remove_artist(int x);

    void on_last_fm_artist_finded(find_artist_t token);
    void on_facebook_artist_finded(find_artist_t token);

    void on_concert_find_counter(void);




signals:

   void lastfm_downloading_finshed(bool);
   void facebook_downloading_finshed(bool);
   void downloading_finshed(bool);
   void add_to_progress_bar(int );
   void add_message_info_label(QString );

   void empty_artist_record(ArtistToken);
   void artist_record(ArtistToken);
    void actualize_artist_list(void);

    void last_fm_artis_find(find_artist_t);
     void facebook_artis_find(find_artist_t);

    void event_searching_finished(int);





};

#endif // APPENGINE_H
