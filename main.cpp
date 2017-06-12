#include "mainwindow.h"
#include <QApplication>


void redirectCoutToFile(string fileName){
    freopen(fileName.c_str(),"w",stdout);
}


int main(int argc, char *argv[])
{
//    QApplication::addLibraryPath(("plugins/"));




    redirectCoutToFile("log.txt");
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Wyszukiwacz Koncertow");
    w.show();

    return a.exec();
}
