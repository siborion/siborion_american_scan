#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bases.h"
#include "scanbase.h"
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
    Scanbase *scanbase;
    StPatient *curPatient;

signals:
    void refreshFormula();

Q_SIGNALS:
    void changeSideSignal();


};

#endif // MAINWINDOW_H
