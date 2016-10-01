#include "BScanHard.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
//#include <QtTest/QTest>

QMutex mutex;
QMutex mutexBuf1;
QMutex mutexBuf2;
QMutex mutexBuf3;
QMutex mutexStart;
QMutex mutexLastBuf;


BScanHard::BScanHard(QObject *parent) :
    QObject(parent)
{
    lastBuf = 1;
    mutexStart.lock();
    doStart = doStop = false;
    mutexStart.unlock();

    for(quint32 i=0; i<NumVectors*NumPoints; i++)
    {
        buf1[i] = qrand();
    }

    //    QTest::qSleep(500);
}

void BScanHard::open()
{
}

unsigned char *BScanHard::getBuf()
{

    mutexLastBuf.lock();
    {
        switch(lastBuf)
        {
        case 1:
            //            if(mutexBuf1.tryLock())
            //            {
            //                for(quint32 i=0; i<NumVectors*NumPoints; i++)
            //                {
            //                    b1[i]=buf1[i];
            //                }
            //                mutexBuf1.unlock();
            mutexLastBuf.unlock();
            return buf1;
            //            }
            break;
        case 2:
            //            if(mutexBuf2.tryLock())
            //            {
            //                for(quint32 i=0; i<NumVectors*NumPoints; i++)
            //                {
            //                    b2[i]=buf2[i];
            //                }
            //                mutexBuf2.unlock();
            mutexLastBuf.unlock();
            return buf2;
            //            }
            break;
        case 3:
            //            if(mutexBuf3.tryLock())
            //            {
            //                for(quint32 i=0; i<NumVectors*NumPoints; i++)
            //                {
            //                    b3[i]=buf3[i];
            //                }
            //                mutexBuf3.unlock();
            mutexLastBuf.unlock();
            return buf3;
            //            }
            break;
        }
    }



    mutexLastBuf.unlock();

    return buf1;
}

void BScanHard::close()
{
    mutex.lock();
    doBScanHard = false;
    mutex.unlock();
}

void BScanHard::read()
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

    cur = 0;
    j = 0;

    sendRun(true);

    while(true)
    {

        qDebug()<<"read";

        if(mutex.tryLock())
        {
            if(!doBScanHard)
            {
                mutex.unlock();
                break;
            }
            mutex.unlock();
        }

        //        if(mutexStart.tryLock())
        //        {
        //            if((doStart))
        //            {

        //                doStart = false;

        //                sendRun(true);

        //            }
        //            mutexStart.unlock();
        //        }

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

                                j=0;
                                cur = 2;
                                mutexLastBuf.lock();
                                lastBuf = 1;
                                mutexLastBuf.unlock();
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

                                j=0;
                                cur = 3;
                                mutexLastBuf.lock();
                                lastBuf = 2;
                                mutexLastBuf.unlock();
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

                                j=0;
                                cur = 1;
                                mutexLastBuf.lock();
                                lastBuf = 3;
                                mutexLastBuf.unlock();
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
    sendRun(false);
    ftStatus = FT_ResetDevice(ftHandle);

    ftStatus = FT_Close(ftHandle);



}

void BScanHard::process()
{
    mutexStart.lock();
    doStart = true;
    mutexStart.unlock();

    doBScanHard = true;
    QFuture <void> func = QtConcurrent::run(this, &BScanHard::read);

}

void BScanHard::setGain(unsigned char gain)
{
    FT_STATUS ftStatus;
    unsigned char TxBuffer[3];
    DWORD TxBytes;
    DWORD BytesTransmited;
    TxBytes = 3;
    TxBuffer[0] = 0x80;
    TxBuffer[1] = gain>>4;
    TxBuffer[2] = gain&0x0f;
    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);

}
/*
void BScanHard::setRun(bool start)
{

    mutexStart.lock();
//    if(start)
//    {
//        doStart = true;
//        doStop  = false;
//    }
//    else
//    {
//        doStop = true;
//        doStart = false;
//    }
    mutexStart.unlock();

//    sendRun(true);

    FT_STATUS ftStatus;
//    unsigned char TxBuffer[3];
//    DWORD TxBytes;
//    DWORD BytesTransmited;
//    TxBytes = 3;
//    TxBuffer[0] = 0x81;
//    TxBuffer[1] = 0x00;
//    TxBuffer[2] = start?1:0;
//    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);


    unsigned char TxBuffer[5];
    DWORD TxBytes;
    DWORD BytesTransmited;
    TxBytes = 5;
    TxBuffer[0] = 0x82;
    TxBuffer[1] = 0x00;
    TxBuffer[2] = 0x00;
    TxBuffer[3] = 0x00;
    TxBuffer[4] = 0x00;
    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);



    TxBytes = 3;
    TxBuffer[0] = 0x81;
    TxBuffer[1] = 0x00;
    TxBuffer[2] = start?1:0;
    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);
}
*/

void BScanHard::sendRun(bool start)
{
    FT_STATUS ftStatus;
    unsigned char TxBuffer[5];
    DWORD TxBytes;
    DWORD BytesTransmited;

    TxBytes = 3;
    TxBuffer[0] = 0x81;
    TxBuffer[1] = 0x00;
    TxBuffer[2] = start?1:0;
    ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);

    if(start)
    {
        TxBytes = 5;
        TxBuffer[0] = 0x82;
        TxBuffer[1] = 0x00;
        TxBuffer[2] = 0x00;
        TxBuffer[3] = 0x00;
        TxBuffer[4] = 0x00;
        ftStatus = FT_Write(ftHandle, TxBuffer, TxBytes, &BytesTransmited);
    }
}
