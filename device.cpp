#include "device.h"
#include <qdebug.h>
#include <QDateTime>
#include <QApplication>

Device::Device(QObject *parent) :
    QObject(parent)
{
    doDll = true;
    port = new QSerialPort(this);
    timer = new QTimer();
    timer->setInterval(50);
    connect(timer,SIGNAL(timeout()),SLOT(doTimer()));
}

void Device::openDevice(bool *link)
{
    QStringList lsName;
    doMeasure = link;
    QString str;
    str.append("\\\\.\\");

    if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        if(!(*doMeasure))
        {
            foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            {lsName.append(info.portName());}
            DialogSerial *dialogSerial = new DialogSerial(0, &lsName);
            if(dialogSerial->exec() == QDialog::Accepted)
            {
                str.append(dialogSerial->cbPort->currentText());
                doDll = false;
            }
            else
                doDll =true;
        }
    }

    port->setPortName(str);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->waitForBytesWritten(-1);
    if(*doMeasure)
    {
        if(doDll)
            FT_Close(ftHandle);
        else
            port->close();
        *doMeasure = false;
        timer->stop();
    }
    else
    {
        if(doDll)
        {
            ftStatus = FT_CreateDeviceInfoList (&ftNumDevice);
            if((ftStatus != FT_OK)||(ftNumDevice==0))
                return;
            FT_Out_Buffer[0] = 'A';
            ftStatus = FT_Open(0, &ftHandle);
            if(ftStatus!=FT_OK)
                return;
            FT_SetBaudRate(ftHandle,9600);
            FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x00, 0x00);
            FT_SetDtr(ftHandle);
            FT_SetRts(ftHandle);
            FT_Purge(ftHandle,3);
            *doMeasure = true;
            timer->start();
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
}

void Device::doTimer()
{
    QByteArray baTmp;
    quint16 kolvo = 0;
    DWORD BytesWritten;
    DWORD BytesReceived;
    DWORD BytesReceivedCount;
    char RxBuffer[2048];
    if(doDll)
    {
        FT_GetQueueStatus(ftHandle, &BytesReceivedCount);
        if(BytesReceivedCount>=1023)
        {
            FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);
            FT_Purge(ftHandle,1);
            for(int i=0; i<=1023; i++)
            {
                baTmp.append((unsigned char)(RxBuffer[i]));
                kolvo++;
            }
            emit resiveData(baTmp.left(1024));
        }
        ftStatus = FT_Write(ftHandle, FT_Out_Buffer, 1,  &BytesWritten);
    }
    else
    {
        baTmp = port->readAll();
        port->write("A", 1);
        if(baTmp.count()>=1024)
            emit resiveData(baTmp.left(1024));
    }
}

void Device::stopMeasure()
{
//    bool bMeasure=true;
    openDevice(doMeasure);
}
