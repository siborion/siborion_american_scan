#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bases.h"
#include "measure.h"
#include "scanbase.h"
#include "curparam.h"
#include "device.h"
#include "parcer.h"
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
    Scanbase *scanbase;
    QMap <QString, QString> *curPatient;
    CurParam *curParam;
    Device *device;
    Parcer *parcer;
    void moveWindowToCenter();

public slots:
    void resiveDataSlot(QByteArray);

Q_SIGNALS:

};

#endif // MAINWINDOW_H
