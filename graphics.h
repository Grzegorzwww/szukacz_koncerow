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
      QAction *change_artist_fullname;
      QAction *change_artist_lastfmname;
      QAction *change_artist_facebook;
      QAction *change_artist_songkick;
      QAction *find_similas_artist;
      QAction *show_most_played_with_artists;



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

      void on_dodaj_facebook_clicked(bool x);
      void on_remove_lastfm_pushed(bool x);
      void on_remove_facebook_pushed(bool x);
//      void on_main_tab_changed(int n);
      void on_remove_from_last_fm();
      void on_remove_from_facebook();
      void on_rename_from_last_fm();
      void on_rename_from_facebook();
      void on_enter_pushed();
      void on_tableView_3_customContextMenuRequested(const QPoint &pos);
      void on_tableView_2_customContextMenuRequested(const QPoint &pos);




//      void on_actualice_artist_list(QList <artist_names_t> lista);
      void on_reflash_artist_list(void);
      void lineEdit_focused(bool x) { if(x){ui->my_lineEdit->clear();} else{if(ui->my_lineEdit->text().isEmpty()) ui->my_lineEdit->setText("-");}}
      void lineEdit_2_focused(bool x) {if(x){ui->my_lineEdit_2->clear();} else{if(ui->my_lineEdit_2->text().isEmpty()) ui->my_lineEdit_2->setText("-");}}
      void lineEdit_3_focused(bool x) {if(x){ui->my_lineEdit_3->clear();} else{if(ui->my_lineEdit_3->text().isEmpty()) ui->my_lineEdit_3->setText("-");}}
      void lineEdit_4_focused(bool x) { if(x){ui->my_lineEdit_4->clear();} else{if(ui->my_lineEdit_4->text().isEmpty()) ui->my_lineEdit_4->setText("-");}}
      void lineEdit_5_focused(bool x) { if(x){ui->my_lineEdit_5->clear();} else{if(ui->my_lineEdit_5->text().isEmpty()) ui->my_lineEdit_5->setText("Wpisz...");}}


      void on_remove_artist_from_table_clicked();
      void on_delete_press();



signals:
      void reload_list();
      void added_artist_clicked(artist_names_t token);
      void removed_artist_clicked(int no);
      void delete_press();



};




#endif // GRAPHICS_H
