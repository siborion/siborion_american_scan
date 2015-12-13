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
    /*
    switch(lastBuf)
    {
    case 1:
        if(mutexBuf1.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf1[i];
            }
            mutexBuf1.unlock();
        }
        break;
    case 2:
        if(mutexBuf2.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf2[i];
            }
            mutexBuf2.unlock();
        }
        break;
    case 3:
        if(mutexBuf3.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf3[i];
            }
            mutexBuf3.unlock();
        }
        break;
    }
*/
    return curBuf;
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
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    unsigned char RxBuffer[65536];
    quint8 cur;
    quint32 i;
    quint32 j;

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
    FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x0, 0x0);
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
        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if(RxBytes>0)
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            i = 0;
            //            while (i<BytesReceived)
            //            {
            //                switch(cur)
            //                {
            //                case 0:
            //                case 1:
            //                    if(mutexBuf1.tryLock())
            //                    {

            //            qDebug()<<"BytesReceived"<<BytesReceived;

            while (i<BytesReceived)
            {
                if(RxBuffer[i]==0)
                {
                    if(j!=409600)
                        qDebug()<<j;
                    i++;
                    j=0;
                    cur = 2;
                    lastBuf = 1;
                    //                    break;
                }
                else
                {
                    //                    buf1[j]=RxBuffer[i];
                    j++; i++;
                }
            }



            //                        mutexBuf1.unlock();
            //                    }
            //                    else
            //                        cur = 2;
            //                    break;

            //                case 2:
            //                    if(mutexBuf2.tryLock())
            //                    {
            //                        while (i<BytesReceived)
            //                        {
            //                            if(RxBuffer[i]==0)
            //                            {
            //                                qDebug()<<"j"<<j;
            //                                i++;
            //                                j=0;
            //                                cur =3;
            //                                lastBuf = 2;
            //                                break;
            //                            }
            //                            else
            //                            {
            //                                buf2[j]=RxBuffer[i];
            //                                j++; i++;
            //                            }
            //                        }
            //                        mutexBuf2.unlock();
            //                    }
            //                    else
            //                        cur = 3;
            //                    break;

            //                case 3:
            //                    if(mutexBuf3.tryLock())
            //                    {
            //                        while (i<BytesReceived)
            //                        {
            //                            if(RxBuffer[i]==0)
            //                            {
            //                                qDebug()<<"j"<<j;
            //                                i++;
            //                                j=0;
            //                                cur = 1;
            //                                lastBuf = 3;
            //                                break;
            //                            }
            //                            else
            //                            {
            //                                buf3[j]=RxBuffer[i];
            //                                j++; i++;
            //                            }
            //                        }
            //                        mutexBuf3.unlock();
            //                    }
            //                    else
            //                        cur = 1;
            //                    break;
            //                }
            //            }
        }
    }
    ftStatus = FT_Close(&ftHandle);
}

void Scan::process()
{
    doScan = true;
    QFuture <void> func = QtConcurrent::run(this, &Scan::read);

//          read();
}
