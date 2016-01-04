#include "scan.h"
#include <QDebug>
#include <QtConcurrent>
#include <QMutex>

QMutex mutex;
QMutex mutexBuf1;
QMutex mutexBuf2;
QMutex mutexBuf3;

Scan::Scan(QObject *parent) :
    QObject(parent)
{
}

void Scan::open()
{
}

unsigned char *Scan::getBuf()
{
//    qDebug()<<"lastBuf"<<lastBuf;
    switch(lastBuf)
    {
    case 1:
        if(mutexBuf1.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints; i++)
            {
                tmpBuf[i]=buf1[i];
            }
            mutexBuf1.unlock();
        }
        break;
    case 2:
        if(mutexBuf2.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints; i++)
            {
                tmpBuf[i]=buf2[i];
            }
            mutexBuf2.unlock();
        }
        break;
    case 3:
        if(mutexBuf3.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints; i++)
            {
                tmpBuf[i]=buf3[i];
            }
            mutexBuf3.unlock();
        }
        break;
    }
//    return curBuf;
    return tmpBuf;
}

void Scan::close()
{
    mutex.lock();
    doScan = false;
    mutex.unlock();
}

void Scan::read()
{
    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD BytesReceived;
    unsigned char RxBuffer[65536];
    quint8 cur;
    quint32 i;
    quint32 j;

    FT_DEVICE_LIST_INFO_NODE *devInfo;
    DWORD numDevs;
    // create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus == FT_OK) {
        qDebug("Number of devices is %d",numDevs);
    }
    if (numDevs > 0) {
        // allocate storage for list based on numDevs
        devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
        // get the device information list
        ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
        if (ftStatus == FT_OK) {
            for (int i = 0; i < numDevs; i++) {
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

    cur = 0;
    j = 0;

    while(true)
    {
        if(mutex.tryLock())
        {
            if(!doScan)
            {
                mutex.unlock();
                qDebug()<<"return";
                break;
            }
            mutex.unlock();
        }

        FT_GetQueueStatus(ftHandle, &RxBytes);
        if(RxBytes>0)
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            i = 0;
            while (i<BytesReceived)
            {
                switch(cur)
                {
                case 0:
                case 1:
                    if(mutexBuf1.tryLock())
                    {
                        while (i<BytesReceived)
                        {
                            if(RxBuffer[i]==0)
                            {
//                                qDebug()<<j;
                                j=0;
                                cur = 2;
                                lastBuf = 1;
                                i++;
                                break;
                            }
                            else
                            {
                                buf1[j]=RxBuffer[i];
                                j++;
                            }
                            i++;
                        }
                        mutexBuf1.unlock();
                    }
                    else
                        cur = 2;
                    break;

                case 2:
                    if(mutexBuf2.tryLock())
                    {
                        while (i<BytesReceived)
                        {
                            if(RxBuffer[i]==0)
                            {
//                                qDebug()<<j;
                                j=0;
                                cur = 3;
                                lastBuf = 2;
                                i++;
                                break;
                            }
                            else
                            {
                                buf2[j]=RxBuffer[i];
                                j++;
                            }
                            i++;
                        }
                        mutexBuf2.unlock();
                    }
                    else
                        cur = 3;
                    break;

                case 3:
                    if(mutexBuf3.tryLock())
                    {
                        while (i<BytesReceived)
                        {
                            if(RxBuffer[i]==0)
                            {
//                                qDebug()<<j;
                                j=0;
                                cur = 1;
                                lastBuf = 3;
                                i++;
                                break;
                            }
                            else
                            {
                                buf3[j]=RxBuffer[i];
                                j++;
                            }
                            i++;
                        }
                        mutexBuf3.unlock();
                    }
                    else
                        cur = 1;
                    break;
                }
            }
        }
    }
    ftStatus = FT_ResetDevice(ftHandle);
    qDebug()<<"ftStatus"<<ftStatus;
    ftStatus = FT_Close(ftHandle);
    qDebug()<<"ftStatus"<<ftStatus;
    qDebug()<<"close";
}

void Scan::process()
{
    doScan = true;
    QFuture <void> func = QtConcurrent::run(this, &Scan::read);

    //          read();
}

void Scan::setGain(unsigned char gain)
{
    FT_STATUS ftStatus;
    unsigned char TxBuffer[3];
    DWORD TxBytes;
    DWORD BytesTransmited;

    TxBytes = 3;
    TxBuffer[0] = 0x80;
    TxBuffer[1] = gain>>8;
    TxBuffer[2] = gain&0x0f;
    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);

    qDebug()<<"WRITE"<<ftStatus;

}

