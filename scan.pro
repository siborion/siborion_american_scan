#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T17:01:48
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=gnu++11


QT       += core gui
QT	 += serialport
#QT       += svg

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
	panel.cpp\
        scanplot.cpp\
        mesurement.cpp\
    bases.cpp \
    adjview.cpp \
    patient.cpp \
    doctor.cpp \
    lens.cpp \
    calculator.cpp \
    mydelegate.cpp \
    formula.cpp


HEADERS  += mainwindow.h\
	panel.h\
        scanplot.h\
	mesurement.h \
    bases.h \
    adjview.h \
    patient.h \
    doctor.h \
    lens.h \
    calculator.h \
    mydelegate.h \
    formula.h

#FORMS    += mainwindow.ui

RESOURCES += \
    scan.qrc
