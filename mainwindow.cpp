#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    appEngine = new AppEngine(ui, this);
    connect(this, SIGNAL(enter_pushed_signal()), appEngine, SLOT(on_enter_pushed()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_Enter){
         qDebug() << "ENTER";
         emit enter_pushed_signal();
    }

    //this->setFocus();
}
