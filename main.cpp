#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath(("plugins/"));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Wyszukiwacz Koncertow");
    w.show();

    return a.exec();
}
