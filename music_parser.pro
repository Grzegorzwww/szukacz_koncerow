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
    htmlparser.cpp \
    event_token.cpp \
    filemanager.cpp

HEADERS  += mainwindow.h \
    nameparser.h \
    appengine.h \
    htmlparser.h \
    event_token.h \
    filemanager.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

