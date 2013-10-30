#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T17:01:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(qwt.prf)

TARGET = scan
TEMPLATE = app

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

#LIBS      += -L"C:\Qt\Qwt-6.1.0\lib" -lqwt

SOURCES += main.cpp\
        mainwindow.cpp\
        plot.cpp\
	panel.cpp\
	knob.cpp

HEADERS  += mainwindow.h\
        plot.h\
	panel.h\
	knob.h

#FORMS    += mainwindow.ui
