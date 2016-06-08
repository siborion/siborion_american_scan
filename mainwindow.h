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

private:
    Ui::MainWindow *ui;
    Bases *bases;
    Measure *measure;
    calculator *pCalculator;
    Scanbase *scanbase;
    QMap <QString, QString> *curPatient;
    CurParam *curParam;
    Device *device;
    Parcer *parcer;
    Bscan  *bscan;
    QWidget *print;
    void moveWindowToCenter();

public slots:
    void resiveDataSlot(QByteArray*);
    void setStPatient(QMap <QString, QString> *stPatientBases);

private slots:
//    void updatePatient();


Q_SIGNALS:

};

#endif // MAINWINDOW_H
