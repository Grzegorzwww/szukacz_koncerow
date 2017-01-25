#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T14:15:47
#
#-------------------------------------------------

QT       += core gui

QT  +=  network

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
    filelog.cpp

HEADERS  += mainwindow.h \
    nameparser.h \
    appengine.h \
    event_token.h \
    filemanager.h \
    fbparser.h \
    lastfm_parser.h \
    appsetting.h \
    graphics.h \
    filelog.h

FORMS    += mainwindow.ui \
    appsetting.ui

CONFIG += mobility
MOBILITY = 

