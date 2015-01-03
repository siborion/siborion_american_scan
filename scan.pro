#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T19:18:06
#
#-------------------------------------------------

QT       += sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bases.cpp \
    adjview.cpp \
    scanbase.cpp \
    dialog_doctor.cpp \
    dialog_lens.cpp \
    dialog_patient.cpp \
    basefill.cpp \
    combo_delegate.cpp \
    delegate.cpp

HEADERS  += mainwindow.h \
    bases.h \
    adjview.h \
    scanbase.h \
    dialog_doctor.h \
    dialog_lens.h \
    dialog_patient.h \
    typedef.h \
    basefill.h \
    delegate.h \
    combo_delegate.h

FORMS    += mainwindow.ui \
    dialog_doctor.ui \
    dialog_lens.ui

RESOURCES += \
    scan.qrc
