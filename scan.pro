#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T17:01:48
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=gnu++11


QT       += core gui
QT	 += serialport
QT       += sql

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
        mesurement.cpp\
    bases.cpp \
    adjview.cpp \
    patient.cpp \
    doctor.cpp \
    lens.cpp \
    calculator.cpp \
    mydelegate.cpp \
    formula.cpp \
    dbacces.cpp \
    plot.cpp \
    bigview.cpp \
    bigviewnum.cpp \
    key.cpp \
    key_radio.cpp \
    scanbase.cpp \
    basefill.cpp \
    dialog_lens.cpp \
    dialog_doctor.cpp \
    history.cpp \
    bigviewnumhor.cpp \
    sampletable.cpp \
    bigviewnumcur.cpp \
    combo_delegate.cpp \
    delegate.cpp \
    calc.cpp \
    calculator_patient.cpp \
    leaddzero.cpp \
    sampleinterval.cpp \
    curentparam.cpp \
    buttonscan.cpp \
    scanbutton.cpp \
    parserfront.cpp \
    checkboxdelegate1.cpp


HEADERS  += mainwindow.h\
	panel.h\
	mesurement.h \
    bases.h \
    adjview.h \
    patient.h \
    doctor.h \
    lens.h \
    calculator.h \
    mydelegate.h \
    formula.h \
    dbacces.h \
    plot.h \
    bigview.h \
    bigviewnum.h \
    key.h \
    key_radio.h \
    scanbase.h \
    basefill.h \
    dialog_lens.h \
    dialog_doctor.h \
    history.h \
    bigviewnumhor.h \
    sampletable.h \
    bigviewnumcur.h \
    combo_delegate.h \
    delegate.h \
    calc.h \
    calculator_patient.h \
    leaddzero.h \
    typedef.h \ 
    sampleinterval.h \
    curentparam.h \
    buttonscan.h \
    scanbutton.h \
    parserfront.h \
    checkboxdelegate1.h

#FORMS    += mainwindow.ui

RESOURCES += \
    scan.qrc

FORMS += \
    bigviewnum.ui \
    dialog_lens.ui \
    dialog_doctor.ui \
    bigviewnumhor.ui \
    bigviewnumcur.ui \
    calculator_patient.ui \
    buttonscan.ui

OTHER_FILES += plugins/sqldrivers/qsqlite.dll
