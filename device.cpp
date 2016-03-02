#include "device.h"
#include <qdebug.h>
#include <QDateTime>
#include <QTime>
#include <QApplication>
#include <QMessageBox>
#include <QSettings>

#define comLen 1

Device::Device(QObject *parent) :
    QObject(parent)
{
    doDll = true;
    port = new QSerialPort(this);
    timer = new QTimer();
    timer->setInterval(60);
    connect(timer,SIGNAL(timeout()),SLOT(doTimer()));
}

void Device::openDevice(bool *link)
{
    unsigned char TxBuffer[5];
    DWORD TxBytes;
    DWORD BytesTransmited;

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
        TxBuffer[0] = 0x81;
        TxBuffer[1] = 0x00;
        TxBuffer[2] = 0x01;
        ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);
        FT_Close(ftHandle);
        *doMeasure = false;
        timer->stop();
    }
    else
    {
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


            QSettings settings("scan.ini", QSettings::IniFormat);
            settings.beginGroup("a-scan");
            quint8 nomVektor = settings.value("nomVektor", 127).toUInt();
            settings.endGroup();
            qDebug()<<"nomVektor"<<nomVektor;

            TxBytes = 5;
            TxBuffer[0] = 0x82;
            TxBuffer[1] = 0x00;
            TxBuffer[2] = 0x01;
            TxBuffer[3] = nomVektor>>4;
            TxBuffer[4] = nomVektor&0x0f;
            ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);

            TxBuffer[0] = 0x81;
            TxBuffer[1] = 0x00;
            TxBuffer[2] = 0x01;
            ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);

            *doMeasure = true;
            timer->start();

    }
}

void Device::doTimer()
{
//    baTmp.clear();
    FT_GetQueueStatus(ftHandle, &BytesReceivedCount);
//    qDebug()<<BytesReceivedCount;
    if(BytesReceivedCount>=5000)
        BytesReceivedCount=5000;

    FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);

    for(DWORD i=0; i<BytesReceived; i++)
    {
        if(RxBuffer[i]==0)
            baTmp.clear();
        else
        {
            if(RxBuffer[i]==1)
                RxBuffer[i]=0;
            baTmp.append(RxBuffer[i]);
        }

        if(baTmp.size()>=1024)
        {
            emit resiveData(&baTmp);
            baTmp.clear();
        }
    }
//        qDebug()<<baTmp.size();
}

void Device::stopMeasure()
{
    openDevice(doMeasure);
}
