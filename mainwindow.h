#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bases.h"
#include "measure.h"
#include "calculator.h"
#include "scanbase.h"
#include "curparam.h"
#include "device.h"
#include "bscan.h"
#include "parcer.h"
#include "typedef.h"
#include "print.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    Bases *bases;
    Measure *measure;
    calculator *pCalculator;
    Scanbase *scanbase;
    QMap <QString, QString> *curPatient;
    CurParam *curParam;
    Device *device;
    Parcer *parcer;
    Bscan  *bscan;
    Print *print;
    void moveWindowToCenter();

public slots:
    void resiveDataSlot(QByteArray*);
    void setStPatient(QMap <QString, QString> *stPatientBases);
    void slChangeTab(int);

private slots:
//    void updatePatient();


Q_SIGNALS:

};

#endif // MAINWINDOW_H
