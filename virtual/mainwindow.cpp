#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = new Plot(this, false);
    port = new QSerialPort();

//    timer = new QTimer();
//    timer->start(1000);

    cbPort  = new QComboBox();
    cbPort->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {cbPort->addItem(info.portName());}

    pbPort = new QPushButton();
    pbPort->setText("Open");

    leCount = new QLabel("0");

    for(int i=0; i<1024; i++)
        {x[i]=i;y[i]=0;}

    y[9]=255;
    y[148]=255;
    y[239]=255;
    y[695]=255;

    plot->drawSample(x, y, 1024);

    ui->gridLayout->addWidget(plot,   0, 0, 1, 10);
    ui->gridLayout->addWidget(cbPort, 1, 0);
    ui->gridLayout->addWidget(pbPort, 1, 1);
    ui->gridLayout->addWidget(leCount,1, 2);

    connect(plot, SIGNAL(moveSample(quint16,quint8)), SLOT(moveSample(quint16,quint8)));
    connect(pbPort, SIGNAL(clicked()), SLOT(openPort()));
    connect(port, SIGNAL(readyRead()), SLOT(readPort()));
//    connect(timer, SIGNAL(timeout()), SLOT(readPort()));
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

    QByteArray baTmp;
    double dTmp;
    unsigned char rnd;
    port->readAll();


    for(quint16 i=0; i<1024; i++)
    {
        if(i==500)
        {
            rnd = qrand();
            rnd /= 10;

            for(quint16 j=0; j<rnd; j++)
            {
//                i++;
                qDebug()<<"------------------------";
//                baTmp.append((char)0);
            }
        }


        dTmp = (y[i]/2);
        rnd = 0;
        if(dTmp>80)
        {
            rnd = qrand();
            rnd /= 100;
        }
        baTmp.append((char)(dTmp-rnd));
    }
    port->write(baTmp);
    count++;
    leCount->setText(QString("%1").arg(count));
}

MainWindow::~MainWindow()
{
    delete ui;
}
