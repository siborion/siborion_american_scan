#include "device.h"
#include <qdebug.h>
#include <QDateTime>
#include <QTime>
#include <QApplication>
#include <QMessageBox>

#define comLen 1

Device::Device(QObject *parent) :
    QObject(parent)
{
    doDll = true;
    port = new QSerialPort(this);
    timer = new QTimer();
    timer->setInterval(68);
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
    port->setFlowControl(QSerialPort::HardwareControl);
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
            FT_Out_Buffer[1] = 'T';
            FT_Out_Buffer[2] = '+';
            FT_Out_Buffer[3] = 'G';
            FT_Out_Buffer[4] = 'M';
            FT_Out_Buffer[5] = 'I';
            FT_Out_Buffer[6] = 0x0d;
            FT_Out_Buffer[7] = 0x0a;
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
                port->setRequestToSend(true);
                port->setDataTerminalReady(true);
                *doMeasure = true;
                timer->start();
            }
        }
    }
}

void Device::doTimer()
{
    baTmp.clear();
    if(doDll)
    {
        FT_GetQueueStatus(ftHandle, &BytesReceivedCount);

//        QMessageBox msg;
//        msg.setText(QString("%1").arg(BytesReceivedCount));
//        msg.exec();

        qDebug()<<BytesReceivedCount;

        FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);

        if(BytesReceivedCount==1024)
//        if(BytesReceivedCount>=27)
        {
//            qDebug()<<QTime::currentTime().msec();
//            BytesReceivedCount &= 0x3ff;
            FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);
            FT_Purge(ftHandle,1);
//            ftStatus = FT_Write(ftHandle, FT_Out_Buffer, comLen, &BytesWritten);
            baTmp.append(RxBuffer,1023);
            emit resiveData(&baTmp);
        }
        else
        {
//            qDebug()<<"-"<<QTime::currentTime().msec();
            FT_Purge(ftHandle,1);
//            ftStatus = FT_Write(ftHandle, FT_Out_Buffer, comLen, &BytesWritten);
        }
    }
    else
    {
        baTmp=port->read(1024);
        port->readAll();
        port->write("AT+GMI\r\n", comLen);
        if(baTmp.length()>=1024)
            emit resiveData(&baTmp);
    }
}

void Device::stopMeasure()
{
//    bool bMeasure=true;
    openDevice(doMeasure);
}
