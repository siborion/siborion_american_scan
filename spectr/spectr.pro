#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T20:05:44
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spectr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scan.cpp

HEADERS  += mainwindow.h\
    ftd2xx.h \
    scan.h

FORMS    += mainwindow.ui

LIBS += ftd2xx.lib
