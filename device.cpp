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
//            FT_STATUS ftStatus;
//            DWORD RxBytes;
//            DWORD BytesReceived;
//            unsigned char RxBuffer[65536];
//            quint8 cur;
//            quint32 i;
//            quint32 j;

            FT_DEVICE_LIST_INFO_NODE *devInfo;
            DWORD numDevs;
            // create the device information list
            ftStatus = FT_CreateDeviceInfoList(&numDevs);
            if (ftStatus == FT_OK)
                qDebug("Number of devices is %d",numDevs);

            if (numDevs > 0)
            {
                // allocate storage for list based on numDevs
                devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
                // get the device information list
                ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
                if (ftStatus == FT_OK)
                {
                    for (int i = 0; i < numDevs; i++)
                    {
                        qDebug("Dev %d:", i);
                        qDebug("  Flags=0x%x", devInfo[i].Flags);
                        qDebug("  Type=0x%x", devInfo[i].Type);
                        qDebug("  ID=0x%x", devInfo[i].ID);
                        qDebug("  LocId=0x%x", devInfo[i].LocId);
                        qDebug("  SerialNumber=%s", devInfo[i].SerialNumber);
                        qDebug("    Description=%s", devInfo[i].Description);
                        qDebug("  ftHandle=0x%x", devInfo[i].ftHandle);
                    }
                }
            }

            UCHAR Mask = 0xFF;
            UCHAR Mode = 0x40; // 0x40 = Single Channel Synchronous 245 FIFO Mode (FT2232H and FT232H devices only)
            ftStatus = FT_Open(0, &ftHandle);
            if(ftStatus != FT_OK) {
                // FT_Open failed
                qDebug("FT_Open failed");
                return;
            }
            ftStatus = FT_ResetDevice(ftHandle);
            if (ftStatus == FT_OK) {
                // FT_ResetDevice OK
                qDebug("FT_ResetDevice OK");
            }
            else {
                // FT_ResetDevice failed
                qDebug("FT_ResetDevice failed");
            }
            ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
            if (ftStatus == FT_OK) {
                // 0xff written to device
                qDebug("FT_SetBitMode SUCCESS!");
            }
            else {
                // FT_SetBitMode FAILED!
                qDebug("FT_SetBitMode FAILED!");
            }
            FT_SetLatencyTimer(ftHandle, 2);
            FT_SetUSBParameters(ftHandle, 0x10000, 0x10000);
            FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0x0, 0x0);
            FT_Purge(ftHandle, FT_PURGE_RX);
            FT_Purge(ftHandle, FT_PURGE_TX);

            unsigned char TxBuffer[5];
            DWORD TxBytes;
            DWORD BytesTransmited;
            TxBytes = 5;
            TxBuffer[0] = 0x82;
            TxBuffer[1] = 0x00;
            TxBuffer[2] = 0x01;
            TxBuffer[3] = 0x01;
            TxBuffer[4] = 0x01;
            ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);



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
        if(BytesReceivedCount>=2048)
            BytesReceivedCount=2048;

        FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);

        if(BytesReceivedCount>=1600)
//        if(BytesReceivedCount>=27)
        {
//            qDebug()<<QTime::currentTime().msec();
//            BytesReceivedCount &= 0x3ff;
//            FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);
//            FT_Purge(ftHandle,1);
//            ftStatus = FT_Write(ftHandle, FT_Out_Buffer, comLen, &BytesWritten);
            baTmp.append(RxBuffer,1023);
            emit resiveData(&baTmp);
        }
        else
        {
//            qDebug()<<"-"<<QTime::currentTime().msec();
//            FT_Purge(ftHandle,1);
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
