#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T20:05:44
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spectr
TEMPLATE = app

include(qwt.prf)

CONFIG(debug, debug|release)
{
  LIBS += -lqwt -LC:\Qt\Qwt-6.1.0\lib
}

CONFIG(release, debug|release)
{
  LIBS +=  -lqwtd -LC:\Qt\Qwt-6.1.0\lib
}


SOURCES += main.cpp\
        mainwindow.cpp \
    scan.cpp \
    plot.cpp \
    rasterdata.cpp

HEADERS  += mainwindow.h\
    ftd2xx.h \
    scan.h \
    plot.h \
    rasterdata.h

FORMS    += mainwindow.ui

LIBS += ftd2xx.lib
