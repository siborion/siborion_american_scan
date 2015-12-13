#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QThread* thread = new QThread;
    scan = new Scan();

    timer = new QTimer();
    timer->setInterval(66);
    timer->start();

    plot = new Plot(this, scan->getBuf());

    ui->gridLayout->addWidget(plot,1,0,1,3);

//    scan->moveToThread(thread);

//    connect(thread, SIGNAL(started()), scan, SLOT(process()));

//    connect(ui->pbOpen,SIGNAL(clicked()),scan,SLOT(open()));
    connect(ui->pbRead,SIGNAL(clicked()),scan,SLOT(process()));
    connect(ui->pbClose,SIGNAL(clicked()),scan,SLOT(close()));
    connect(timer, SIGNAL(timeout()),SLOT(reDraw()));
//    connect(ui->pbOpen,SIGNAL(clicked()),scan,SLOT(open()));

//    thread->start();

}


/*
void MainWindow::on_pbOpen_clicked()
{
    FT_STATUS ftStatus;
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
}

void MainWindow::on_pbRead_clicked()
{
    quint32 kkk = 0;
    quint32 ttt = 0;
    quint32 ttt1 = 0;
    quint8 val=0;

    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    unsigned char RxBuffer[65536];
    do
    {
        FT_GetQueueStatus(ftHandle, &RxBytes);
        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if(RxBytes>0)
        {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            for(quint16 i=0; i<BytesReceived; i++)
            {
                if(RxBuffer[i]==0)
                    first=true;
                else
                {
                    if(first)
                    {
                        first = false;
                        val = RxBuffer[i];
                    }
                    else
                    {
                        val++;
                        if(val==0)
                            val++;
                        if(val!=RxBuffer[i])
                            ttt++;
                        else
                            ttt1++;
                    }
                }
            }
            kkk++;
        }
    } while (kkk<100);
    qDebug()<<"ttt"<<ttt;
    qDebug()<<"ttt1"<<ttt1;
}

void MainWindow::on_pbClose_clicked()
{
    FT_Close(ftHandle);
}
*/

void MainWindow::reDraw()
{
    unsigned char *p;
    p = scan->getBuf();

    plot->updateScan();

//    plot->replot();
//    plot->update();

}


MainWindow::~MainWindow()
{
    delete ui;
}
