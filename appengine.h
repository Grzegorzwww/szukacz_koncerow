#ifndef APPENGINE_H
#define APPENGINE_H




#include <QObject>
#include <QDebug>
#include <QString>
#include <QLinkedList>

#include <nameparser.h>
#include <htmlparser.h>
#include <event_token.h>
#include <filemanager.h>
#include "ui_mainwindow.h"



class AppEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppEngine(Ui::MainWindow *_ui, QObject *parent = 0);

    int actual_tab_set;
    int found_events;
    QObject *my_parent;
    NameParser *name_parser;
    filemanager *file_manager;
    HTMLParser *html_parser;

    Ui::MainWindow *ui;

private:

    QList <QString> artist_list;



signals:

public slots:

    void on_dodaj_clicked(bool x);
     void on_start_clicked(bool x);
     void on_main_tab_changed(int n);
     void on_enter_pushed(void);
     void on_remove_pushed(bool x);
};

#endif // APPENGINE_H
