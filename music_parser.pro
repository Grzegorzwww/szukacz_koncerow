#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T14:15:47
#
#-------------------------------------------------

QT       += core gui

QT  +=  network


CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = music_parser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nameparser.cpp \
    appengine.cpp \
    event_token.cpp \
    filemanager.cpp \
    fbparser.cpp \
    lastfm_parser.cpp \
    appsetting.cpp \
    graphics.cpp \
    filelog.cpp \
    mylineedit.cpp \
    search_artist.cpp \
    findartistdialog.cpp \
    urldownload.cpp \
    disppixfromurl.cpp \
    songkick_parser.cpp \
    gw_class.cpp

HEADERS  += mainwindow.h \
    nameparser.h \
    appengine.h \
    event_token.h \
    filemanager.h \
    fbparser.h \
    lastfm_parser.h \
    appsetting.h \
    graphics.h \
    filelog.h \
    defines.h \
    mylineedit.h \
    search_artist.h \
    findartistdialog.h \
    urldownload.h \
    disppixfromurl.h \
    songkick_parser.h \
    gw_class.h

FORMS    += mainwindow.ui \
    appsetting.ui \
    findartistdialog.ui

CONFIG += mobility
MOBILITY = 

DISTFILES +=

RESOURCES += \
    source_img/trash_icon.qrc

