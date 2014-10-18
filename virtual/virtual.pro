#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T23:03:29
#
#-------------------------------------------------


QT       += core gui 
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(qwt.prf)

config -= debug
config += debug_and_release
CONFIG += build_all

CONFIG(debug, debug|release) {
  LIBS += -lqwtd -LC:\Qt\Qwt-6.1.0\lib
#  LIBS += -L"C:\Qt\Qwt-6.1.0\lib" -lqwt
}
CONFIG(release, debug|release) {
  LIBS +=  -lqwt -LC:\Qt\Qwt-6.1.0\lib
}


TARGET = virtual
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    plot.h

FORMS    += mainwindow.ui
