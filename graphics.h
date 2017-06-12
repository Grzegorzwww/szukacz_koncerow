#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QPoint>
#include <QMap>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <mylineedit.h>
#include <QAbstractListModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include "ui_mainwindow.h"
#include <event_token.h>
#include <appsetting.h>
#include <filemanager.h>


class Graphics :  public QWidget
{
    Q_OBJECT
public:
    explicit Graphics(Ui::MainWindow *_ui,QWidget *parent = 0);
    ~Graphics();
    Ui::MainWindow *ui;

    void getDefaultSettings( stettings_t app_sett);
    void getArtisListAdress(QList<artist_names_t> *lista);
    void delete_key_press() {emit delete_press();}


private:
      QStandardItemModel *_result_table_model;
      QStandardItemModel *_artist_table_model;

      QDate *actual_date;
      stettings_t app_stettings;
      QWidget *my_parent;
      bool actual_event_was_find;

      QMenu  *artist_list_menu;
      QAction *remove_from_artist_list;
      QAction *search_in_selected_artist;
      QAction *change_artist_fullname;
      QAction *change_artist_lastfmname;
      QAction *change_artist_facebook;
      QAction *change_artist_songkick;
      QAction *find_similas_artist;
      QAction *show_most_played_with_artists;

       int progrescounter;
       int max_tags_to_search;


      QList <artist_names_t> *lista_wykonawcow;



      bool checkActualDate(QString temp_date);
      void refresh_artist_list_tab();
      void refresh_facebook_artist_tab();
      void createTableWidged();
      void actualizeProgressBar(int artist_last_fm, int artist_facebook);
      void fillRecord(int no, ArtistToken token);
      bool isPolish(QString token_country);
      void inicjalice_gui();


protected:



public slots:

      void on_empty_result_data(ArtistToken token);
      void on_result_data(ArtistToken token);
      void on_clear_result_list(bool x);
      void on_clear_artist_table(bool x);
      void on_get_settings(stettings_t set);
      void on_dodaj_artist_to_list_clicked(bool x);
      void on_enter_pushed();

      void on_tableView_3_customContextMenuRequested(const QPoint &pos);
      void on_tableView_2_customContextMenuRequested(const QPoint &pos);

      void on_sarch_for_artist(QString key_word);

      void on_reflash_artist_list(void);

      void lineEdit_focused(bool x);
      void lineEdit_2_focused(bool x);
      void lineEdit_3_focused(bool x);
      void lineEdit_4_focused(bool x);
      void lineEdit_5_focused(bool x);


      void on_remove_artist_from_table_clicked();
      void on_search_only_selected();
      void on_delete_press();

       void on_sarch_in_artist_list(QString key_word);

       void on_change_artist_full_name();
       void on_change_artist_lastfm_name();
       void on_change_artist_facebook_name();
       void on_change_artist_songkick_name();


      void  on_artist_was_find(QString name);
      void  on_artist_was_not_find(QString name);

      void   on_facebook_artist_was_find(QString name);
      void   on_facebook_artist_was_not_find(QString name);



signals:
      void reload_list();
      void added_artist_clicked(artist_names_t token);
      void removed_artist_clicked(int no);
      void delete_press();

      void concert_find_counter(void);

      void search_for_last_fm_artist(QString);
      void search_for_facebook_artist(QString);

      void search_in_selected_artist_signal(QList<int>);



};




#endif // GRAPHICS_H
