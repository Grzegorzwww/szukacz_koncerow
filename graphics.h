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
#include <QAbstractListModel>
#include <QStandardItem>
#include <QStandardItemModel>
#include "ui_mainwindow.h"
#include <event_token.h>
#include <appsetting.h>
#include <filemanager.h>

class Graphics :  public filemanager
{
    Q_OBJECT
public:
    explicit Graphics(Ui::MainWindow *_ui,QWidget *parent = 0);
    ~Graphics();
    Ui::MainWindow *ui;

    void getDefaultSettings( stettings_t app_sett);



private:
      QStandardItemModel *_result_table_model;
       QStandardItemModel *_artist_table_model;
      QStandardItemModel *_facebook_table_model;
      QDate *actual_date;
      stettings_t app_stettings;
      QWidget *my_parent;
      bool actual_event_was_find;

      QMenu  *lastfm_list_menu;
      QMenu  *facebook_list_menu;
      QAction *remove_from_lastfm_list;
      QAction *rename_from_lastfm_list;
      QAction *remove_from_facebook_list;
      QAction *rename_from_facebook_list;



      bool checkActualDate(QString temp_date);
      void refresh_lastfm_artist_tab();
      void refresh_facebook_artist_tab();
      void createTableWidged();
      void actualizeProgressBar(int artist_last_fm, int artist_facebook);
      void fillRecord(int no, ArtistToken token);
      bool isPolish(QString token_country);
      filemanager *file_manager;


public slots:

      void on_empty_result_data(ArtistToken token);
      void on_result_data(ArtistToken token);
      void on_clear_result_list(bool x);
      void on_get_settings(stettings_t set);

      void on_dodaj_lastfm_clicked(bool x);
      void on_dodaj_facebook_clicked(bool x);
      void on_remove_lastfm_pushed(bool x);
      void on_remove_facebook_pushed(bool x);
      void on_main_tab_changed(int n);
      void on_remove_from_last_fm();
      void on_remove_from_facebook();
      void on_rename_from_last_fm();
      void on_rename_from_facebook();
      void on_enter_pushed();
      void on_tableView_3_customContextMenuRequested(const QPoint &pos);
      void on_tableView_2_customContextMenuRequested(const QPoint &pos);

signals:
      void reload_list();


};

#endif // GRAPHICS_H
