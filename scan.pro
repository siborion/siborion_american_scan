#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T19:18:06
#
#-------------------------------------------------

QT       += sql
QT       += core gui
QT	 += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scan
TEMPLATE = app

include(qwt.prf)

CONFIG(debug, debug|release)
{
  LIBS += -lqwt -LC:\Qt\Qwt-6.1.0\lib
}
CONFIG(release, debug|release)
{
  LIBS +=  -lqwt -LC:\Qt\Qwt-6.1.0\lib
}


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
    delegate.cpp \
    plot.cpp \
    sampleinterval.cpp \
    measure.cpp \
    bigviewnumcur.cpp \
    key_radio.cpp \
    sampletable.cpp \
    velosity.cpp \
    scanbutton.cpp \
    bigviewnum.cpp \
    device.cpp \
    curparam.cpp \
    parcer.cpp

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
    combo_delegate.h \
    plot.h \
    sampleinterval.h \
    measure.h \
    bigviewnumcur.h \
    key_radio.h \
    sampletable.h \
    velosity.h \
    scanbutton.h \
    bigviewnum.h \
    device.h \
    curparam.h \
    parcer.h

FORMS    += mainwindow.ui \
    dialog_doctor.ui \
    dialog_lens.ui \
    bigviewnumcur.ui \
    velosity.ui \
    bigviewnum.ui

RESOURCES += \
    scan.qrc

OTHER_FILES += \
    qwt.prf
