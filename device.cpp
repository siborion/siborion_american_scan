#include "device.h"

Device::Device(QObject *parent) :
    QObject(parent)
{
    port = new QSerialPort(this);
    timer = new QTimer();
    timer->setInterval(50);
}

void Device::openDevice(bool *doMeasure)
{
    QString str;
    str.append("\\\\.\\");
    str.append("COM1");
    port->setPortName(str);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->waitForBytesWritten(-1);

    if(*doMeasure)
    {
        port->close();
        *doMeasure = false;
        timer->stop();
    }
    else
    {
        if(port->open(QIODevice::ReadWrite))
        {
            *doMeasure = true;
            timer->start();
        }
    }
}
