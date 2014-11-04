#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();
    curentParam = CurentParam::instanse();

    QGridLayout *layoutBot = new QGridLayout(this);

    pBigView = new bigviewnum();
    pBigView->setMinimumHeight(120);
    pBigView->setMaximumHeight(150);

    pBigViewCur = new bigviewnumcur();
    pBigViewCur->setMinimumHeight(50);
    pBigViewCur->setMaximumHeight(50);

    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this, false);
    glPlot->addWidget(pBigViewCur);
    glPlot->addWidget(pPlot,1,0);

    pSampleTable = new sampletable();

    QSpacerItem *vs = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    pKey = new key_radio();
    QPushButton *pbDel = new QPushButton(tr(""));
    QIcon iconDel;
    iconDel.addFile(QStringLiteral(":/test/Del"), QSize(), QIcon::Normal, QIcon::Off);
    pbDel->setIcon(iconDel);
    pbDel->setIconSize(QSize(30, 30));

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    pbMeasure = new ScanButton();
    pbMeasure->setSizePolicy(sizePolicy);
    QIcon icon;
    icon.addFile(QStringLiteral(":/test/scan"), QSize(), QIcon::Normal, QIcon::Off);

    layoutBot->addWidget(fmPlot, 0, 0, 4, 1);
    layoutBot->addWidget(pKey,5,0,1,1);

    port = new QSerialPort(this);
    timer = new QTimer();
    timer->start(1000);

    cbPort  = new QComboBox();
    cbPort->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        cbPort->addItem(info.portName());
    }
    cbPort->addItem("dll");

    QFrame *fmSample = new QFrame();
    fmSample->setFrameShape(QFrame::WinPanel);
    fmSample->setFrameShadow(QFrame::Raised);
    QGridLayout *glSample  = new QGridLayout(fmSample);
    glSample->addWidget(pSampleTable,0,0,1,3);
    glSample->addWidget(cbPort,1,0,1,1);
    glSample->addWidget(pbDel,1,2,1,1);
    fmSample->setFixedHeight(230);

    layoutBot->addWidget(fmSample,0,1);
    layoutBot->addItem(vs,1,1);

    layoutBot->addWidget(pbMeasure,2,1);
    layoutBot->addWidget(pBigView,3,1);

    pPlot->changeKeySlot();

    connect(pbMeasure, SIGNAL(pressed()), SLOT(openPort()));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), pSampleTable, SLOT(refreshTable(stMainParam)));
    connect(pSampleTable, SIGNAL(changeRow(QList<quint16>)), SLOT(changeRow(QList<quint16> )));
    connect(pSampleTable, SIGNAL(refreshMainParam()), SLOT(refreshMainParam()));
    connect(pbDel, SIGNAL(clicked()), pSampleTable, SLOT(delSample()));
//    connect(pKey,  SIGNAL(changeCataractSignal(bool)), pPlot, SLOT(changeCataractSlot(bool)));
//    connect(pKey,  SIGNAL(changeContactSignal(bool)), pPlot, SLOT(changeContactSlot(bool)));
    connect(pKey,  SIGNAL(change()), pPlot, SLOT(changeKeySlot()));
    connect(pKey,  SIGNAL(change()), pSampleTable, SLOT(changeKeySlot()));
    connect(timer, SIGNAL(timeout()), SLOT(doTimer()));

    thread = new Thread();
}


void mesurement::changeRow(QList<quint16> extremum)
{
    double x[2024], y[2024];
    quint16 kolvo = 0;

    foreach (quint8 val, pSampleTable->baSample)
    {
        x[kolvo] = kolvo;
        y[kolvo] = double(val);
        kolvo++;
    }

    pPlot->drawSample(x, y, 1024);
    pPlot->allExtremum = extremum;
    pPlot->drawMarker(pSampleTable->mainParam.Start, "Start");
    pPlot->drawMarker((double)pSampleTable->mainParam.Start,(double)60, Qt::yellow);
    if(pSampleTable->mainParam.L1>0)
    {
        pPlot->drawMarker(pSampleTable->mainParam.L1, "L1");
        pPlot->drawMarker((double)pSampleTable->mainParam.L1,(double)60, Qt::yellow);
    }
    if(pSampleTable->mainParam.L2>0)
    {
        pPlot->drawMarker(pSampleTable->mainParam.L2, "L2");
        pPlot->drawMarker((double)pSampleTable->mainParam.L2,(double)60, Qt::yellow);
    }
    pPlot->drawMarker(pSampleTable->mainParam.Retina, "Retina");
    pPlot->drawMarker((double)pSampleTable->mainParam.Retina,(double)60, Qt::yellow);
}

void mesurement::refreshMainParam()
{
    pBigView->setDisplay();
    pBigViewCur->setDisplay(pSampleTable->resultParam.AL, pSampleTable->resultParam.ACD, pSampleTable->resultParam.LT, pSampleTable->resultParam.Vit);
}

void mesurement::openPort()
{
    QString str;
    if(cbPort->currentText().isEmpty())
    {
        pSampleTable->getFileSample();
        return;
    }
    str = "\\\\.\\" + cbPort->currentText();
    port->setPortName(str);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->waitForBytesWritten(-1);
    doDll = ((cbPort->currentIndex()+1)==cbPort->count());
    qDebug()<<"cbPort->currentIndex()"<<cbPort->currentIndex();
    qDebug()<<"cbPort->count()"<<cbPort->count();

    if(pbMeasure->doMeasure)
        stopMeasure();
    else
    {
        if(doDll)
        {
            ftStatus = FT_CreateDeviceInfoList (&ftNumDevice);
            if((ftStatus != FT_OK)||(ftNumDevice==0))
                return;
            FT_Out_Buffer[0] = 'A';
            FT_Out_Buffer[1] = 'T';
            FT_Out_Buffer[2] = 0x0d;
            FT_Out_Buffer[3] = 0x0a;
            ftStatus = FT_Open(0, &ftHandle);
            if(ftStatus!=FT_OK)
                return;
            FT_SetBaudRate(ftHandle,9600);
            FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x00, 0x00);
            FT_SetDtr(ftHandle);
            FT_SetRts(ftHandle);
//            FT_ClrDtr(ftHandle);
//            FT_ClrRts(ftHandle);
        }
        else
        {
            if(!port->open(QIODevice::ReadWrite))
                return;
        }
        pbMeasure->doMeasure = true;
        qDebug()<<"GOOOOO";
        if(curentParam->regimMeasure == RegimMeasure::AUTOFREEZ)
        {
            QStandardItemModel *model;
            model = (QStandardItemModel*)pSampleTable->twMeas->model();
            model->setRowCount(0);
            curentParam->measureAveAL=curentParam->measureDevAL=curentParam->measureAveACD=0;
            curentParam->measureAveLT=curentParam->measureAveVIT=curentParam->measureDevACD=0;
            curentParam->measureDevLT=curentParam->measureDevVIT=0;
        }
        timer->start(150);
        countMeasure=0;
        pSampleTable->resultParam.AL = pSampleTable->resultParam.ACD = pSampleTable->resultParam.LT = pSampleTable->resultParam.Vit = 0;
        refreshMainParam();
    }
}

void mesurement::doTimer()
{
    QList <quint16> extremum;
    stMainParam mainParam;
    QByteArray baTmp, baTmp2;
    double x[2024], y[2024];
    char tmpBuf[10000];
    quint16 kolvo = 0;
    if(pbMeasure->doMeasure)
    {
        if(doDll)
        {
            ftStatus = FT_Write(ftHandle, FT_Out_Buffer, 1,  &BytesWritten);
            FT_GetQueueStatus(ftHandle, &BytesReceivedCount);
            if(BytesReceivedCount>=1024)
                FT_Read(ftHandle,RxBuffer,1024,&BytesReceived);

            FT_GetQueueStatus(ftHandle, &BytesReceivedCount);
            if(BytesReceivedCount>0)
                FT_Read(ftHandle,tmpBuf,BytesReceivedCount,&BytesReceived);

            baTmp.append(RxBuffer,BytesReceived);
        }
        else
        {
            baTmp = port->readAll();
            port->write("A", 1);
        }

        baTmp2.clear();
        foreach(quint8 val, baTmp)
        {
            val = (val*2);
            baTmp2.append(val);
            x[kolvo] = kolvo;
            y[kolvo] = double((unsigned char)val);
            kolvo++;
            if(kolvo>=1024)
                break;
        }
        if(kolvo>=1024)
        {
            pPlot->drawSample(x, y, kolvo);
            if(pSampleTable->findExtremum(&baTmp2, extremum, mainParam))
            {
                switch(curentParam->regimMeasure)
                {
                case RegimMeasure::AUTO:
                    countMeasure++;
                    pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    if(countMeasure>=1)
                        stopMeasure();
                    break;
                case RegimMeasure::AUTOFREEZ:
                    countMeasure++;
                    pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    if(countMeasure>=10)
                        stopMeasure();
                    break;
                case RegimMeasure::MANUAL:
                    if(countMeasure==0)
                        pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    else
                        pSampleTable->addSampleToTable(baTmp2, mainParam, false);
                    countMeasure=1;
                    break;
                }
            }
        }
    }
}

void mesurement::stopMeasure()
{
    if(doDll)
        FT_Close(ftHandle);
    else
        port->close();
    timer->start(1000);
    pbMeasure->doMeasure = false;
    pSampleTable->goToLastSample();
    refreshMainParam();
}
