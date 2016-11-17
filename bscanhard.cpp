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
    curPage = 0;
    lastBuf = 1;
    mutexStart.lock();
    doStart = doStop = false;
    mutexStart.unlock();

    //    for(quint32 j=0; j<80; j++)
    //    {
    //        for(quint32 i=0; i<NumVectors*NumPoints; i++)
    //        {
    //            if(i&0b1000000)
    //                bufAll[0][j][i] = qrand();
    //            else
    //                bufAll[0][j][i] = 0;
    //        }
    //    }
}

void BScanHard::open()
{
}

unsigned char *BScanHard::getMassiv()
{
    return &bufAll[0][0][0];
}

unsigned char *BScanHard::getBuf()
{
    //!!!!!!!На рабочей версии закоментировать
    //    lastBuf++;
    //    if(lastBuf>=64)
    //        lastBuf = 0;
    qDebug()<<"bufAll[0][lastBuf][0]"<<(&bufAll[0][0][0]);
    return &bufAll[0][lastBuf][0];
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
    //    quint8 curPage;
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

    //    cur = 0;
    j = 0;

    sendRun(true);
    doBScanHard = true;

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

        FT_GetQueueStatus(ftHandle, &RxBytes);
        if(RxBytes>0)
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            i = 0;
            while (i<BytesReceived)
            {
                if(RxBuffer[i]==0)
                {
                    j=0;
                    lastBuf = curBuf;
                    curBuf++;
                    if(curBuf>=64)
                        curBuf = 0;
                    i++;
                }
                else
                {
                    bufAll[curPage][curBuf][j] = RxBuffer[i];
                    j++;
                }
                i++;
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

void BScanHard::slSetSample(quint8 nomTab, quint8 nomRec, QByteArray* smp, quint32* pntr)
{
    quint16 pixel=0;
    pntr = (quint32*)&bufAll[nomTab][nomRec][0];
    foreach (unsigned char val, *smp)
    {
        bufAll[nomTab][nomRec][pixel] = val;
        pixel++;
    }
}

