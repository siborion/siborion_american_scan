#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = new Plot(this, false);

    cbPort  = new QComboBox();
    cbPort->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {cbPort->addItem(info.portName());}

    ui->gridLayout->addWidget(plot,   0, 0, 1, 10);
    ui->gridLayout->addWidget(cbPort, 1, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
