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
    void keyPressEvent(QKeyEvent * event);
    void changeEvent(QEvent *event);


    AppEngine *appEngine;
    AppSetting *appSetting;
    Graphics *graphics;
    Filelog *fileLog;


public slots:



private:
    Ui::MainWindow *ui;


signals:

    void enter_pushed_signal(void);

};

#endif // MAINWINDOW_H
