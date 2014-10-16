#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T23:03:29
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(qwt.prf)

CONFIG(debug, debug|release)
{
  LIBS += -lqwtd -LC:\Qt\Qwt-6.1.0\lib
}
CONFIG(release, debug|release)
{
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
