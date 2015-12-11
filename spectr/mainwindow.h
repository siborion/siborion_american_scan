#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scan.h"
#include <qt_windows.h>

#ifdef _cplusplus
extern "C" {
#endif
#include "ftd2xx.h"
#ifdef _cplusplus
}
#endif

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
    FT_HANDLE ftHandle;
    bool first;
    Scan *scan;

private slots:
//    void on_pbOpen_clicked();
//    void on_pbRead_clicked();
//    void on_pbClose_clicked();
};

#endif // MAINWINDOW_H
