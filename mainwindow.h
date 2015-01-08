#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bases.h"
#include "measure.h"
#include "scanbase.h"
#include "curparam.h"
#include "device.h"
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
    void moveWindowToCenter();

signals:
    void refreshFormula();

Q_SIGNALS:
    void changeSideSignal();


};

#endif // MAINWINDOW_H
