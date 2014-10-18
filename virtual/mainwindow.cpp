#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    plot = new Plot(this, false);
    port = new QSerialPort();

    cbPort  = new QComboBox();
    cbPort->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {cbPort->addItem(info.portName());}

    pbPort = new QPushButton();
    pbPort->setText("Open");

    for(int i=0; i<1024; i++)
        {x[i]=i;y[i]=0;}
    plot->drawSample(x, y, 1024);

    ui->gridLayout->addWidget(plot,   0, 0, 1, 10);
    ui->gridLayout->addWidget(cbPort, 1, 0);
    ui->gridLayout->addWidget(pbPort, 1, 1);

    connect(plot, SIGNAL(moveSample(quint16,quint8)), SLOT(moveSample(quint16,quint8)));
    connect(pbPort, SIGNAL(clicked()), SLOT(openPort()));
//    connect(port,)
}

void MainWindow::moveSample(quint16 newX, quint8 newY)
{
    y[newX] = newY;
}

void MainWindow::openPort()
{
    QString str;
    str = "\\\\.\\" + cbPort->currentText();
    port->setPortName(str);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setReadBufferSize(1024);
    if(port->isOpen())
        port->close();
    else
        port->open(QIODevice::ReadWrite);
    pbPort->setText(port->isOpen()?"Close":"Open");

}

void MainWindow::readPort()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
