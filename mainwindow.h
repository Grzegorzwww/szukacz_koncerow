#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <appengine.h>
#include <QKeyEvent>
#include <QKeySequence>
#include <appsetting.h>
#include <graphics.h>
#include <filelog.h>
#include <artistmanage.h>
#include <findartistdialog.h>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeEvent(QEvent *event);


    AppEngine *appEngine;
    AppSetting *appSetting;
    Graphics *graphics;
    Filelog *fileLog;
    FindArtistDialog *findArtistDialog;


public slots:



private:
    Ui::MainWindow *ui;


protected:
        void keyPressEvent(QKeyEvent *event);


signals:



};

#endif // MAINWINDOW_H
