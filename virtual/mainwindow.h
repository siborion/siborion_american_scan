#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QTimer>
#include "plot.h"

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
    Plot *plot;
    QComboBox *cbPort;
    QPushButton *pbPort;
    double x[1024], y[1024];
    QSerialPort *port;
    QTimer *timer;

public slots:
    void moveSample(quint16, quint8);
    void openPort();
    void readPort();
};

#endif // MAINWINDOW_H
