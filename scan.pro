#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T19:18:06
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=gnu++11

QT       += sql
QT       += core gui
QT	 += serialport
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scan
TEMPLATE = app

include(qwt.prf)
include(../QtRPT/QtRPT.pri)


CONFIG(debug, debug|release)
{
  LIBS += -lqwt -LC:\Qt\Qwt-6.1.0\lib
  LIBS += ftd2xx.lib
}

CONFIG(release, debug|release)
{
  LIBS +=  -lqwtd -LC:\Qt\Qwt-6.1.0\lib
  LIBS += ftd2xx.lib
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
    parcer.cpp \
    parserfront.cpp \
    calculator.cpp \
    formula.cpp \
    calc.cpp \
    calculator_patient.cpp \
    leaddzero.cpp \
    listresult.cpp \
    dialogserial.cpp \
    delegate_lens.cpp \
    printplot.cpp \
    bscan.cpp \
    bscantools.cpp \
    bscancontrol.cpp \
    bscanhard.cpp \
    bscanarrow.cpp \
    bscanvertex.cpp \
    scena.cpp \
    bscanarray.cpp \
    bscantabloa.cpp

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
    parcer.h \
    parserfront.h \
    calculator.h \
    formula.h \
    calculator_patient.h \
    calc.h \
    leaddzero.h \
    listresult.h \
    ftd2xx.h \
    dialogserial.h \
    delegate_lens.h \
    printplot.h \
    bscan.h \
    bscantools.h \
    bscancontrol.h \
    bscanhard.h \
    bscanarrow.h \
    bscanvertex.h \
    scena.h \
    bscanarray.h \
    bscantabloa.h

FORMS    += mainwindow.ui \
    dialog_doctor.ui \
    dialog_lens.ui \
    bigviewnumcur.ui \
    velosity.ui \
    bigviewnum.ui \
    calculator_patient.ui \
    listresult.ui \
    dialogserial.ui \
    bscan.ui \
    bscantools.ui \
    bscancontrol.ui \
    bscantabloa.ui

RESOURCES += \
    scan.qrc

OTHER_FILES += \
    qwt.prf \
    plugins/sqldrivers/qsqlite.dll

#OTHER_FILES += plugins/sqldrivers/qsqlite.dll
