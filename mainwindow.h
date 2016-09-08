#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <appengine.h>
#include <QKeyEvent>
#include <QKeySequence>

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

    AppEngine *appEngine;

private:
    Ui::MainWindow *ui;

signals:

    void enter_pushed_signal(void);
};

#endif // MAINWINDOW_H
