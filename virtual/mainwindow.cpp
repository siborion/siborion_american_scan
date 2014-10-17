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

    pbPort = new QPushButton();
    pbPort->setText("Open");

    for(int i=0; i<1024; i++)
        {x[i]=i;}
    plot->drawSample(x, y, 1024);

    ui->gridLayout->addWidget(plot,   0, 0, 1, 10);
    ui->gridLayout->addWidget(cbPort, 1, 0);
    ui->gridLayout->addWidget(pbPort, 1, 1);

    connect (plot, SIGNAL(moveSample(quint16,quint8)), SLOT(moveSample(quint16,quint8)));
}


void MainWindow::moveSample(quint16 newX, quint8 newY)
{
    y[newX] = newY;
}

MainWindow::~MainWindow()
{
    delete ui;
}
