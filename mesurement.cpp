#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();
    curentParam = CurentParam::instanse();

    QList<int> columnPercent;
    QStringList lst;

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
//    lineSelect = new LineSelect(this);

    glPlot->addWidget(pBigViewCur);
//    glPlot->addWidget(lineSelect);
    glPlot->addWidget(pPlot,1,0);
//    glPlot->addWidget(lineSelect,2,2);

//    lst.clear();
//    columnPercent.clear();
//    columnPercent<<10      <<15            <<15      <<15       <<15      <<15;
//    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
//    twMeas  = new adjview(10, lst, columnPercent);
//    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
//    twMeas->setMinimumWidth(300);

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
//    pbMeasure->setIcon(icon);
//    pbMeasure->setIconSize(QSize(50, 50));
//    pbMeasure->setCheckable(true);

    layoutBot->addWidget(fmPlot, 0, 0, 4, 1);
    layoutBot->addWidget(pKey,5,0,1,1);

    port = new QSerialPort(this);
    timer = new QTimer();
//    timer->start(62);
    timer->start(1000);

    cbPort  = new QComboBox();
    cbPort->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        cbPort->addItem(info.portName());
//        cbPort->addItem(info.description());
    }


    QFrame *fmSample = new QFrame();
//    fmSample->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 100);"));
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

    connect(pbMeasure, SIGNAL(pressed()), SLOT(openPort()));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), pSampleTable, SLOT(refreshTable(stMainParam)));
    connect(pSampleTable, SIGNAL(changeRow(QList<quint16>)), SLOT(changeRow(QList<quint16> )));
    connect(pSampleTable, SIGNAL(refreshMainParam()), SLOT(refreshMainParam()));
    connect(pbDel, SIGNAL(clicked()), pSampleTable, SLOT(delSample()));
    connect(pKey,  SIGNAL(changeCataractSignal(bool)), pPlot, SLOT(changeCataractSlot(bool)));
    connect(pKey,  SIGNAL(changeContactSignal(bool)), pPlot, SLOT(changeContactSlot(bool)));
    connect(timer, SIGNAL(timeout()), SLOT(doTimer()));
}

void mesurement::delSample()
{
//    double x[2024], y[2024];
//    quint16 kolvo = 0;
//    for(kolvo=0; kolvo<=1024; kolvo++)
//    {
//        x[kolvo] = kolvo;
//        y[kolvo] = double(255);
//    }
//    pPlot->drawSample(x, y, 1024);

//      QPrinter             printer( QPrinter::HighResolution );
//      QPrintPreviewDialog  preview( &printer, this );
//      connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
//      preview.exec();
}

//void  mesurement::print( QPrinter* printer )
//{
//  // create painter for drawing print page
//  QPainter painter( printer );
//  int      w = printer->pageRect().width();
//  int      h = printer->pageRect().height();
//  QRect    page( 0, 0, w, h );

//  // create a font appropriate to page size
//  QFont    font = painter.font();
//  font.setPixelSize( (w+h) / 100 );
//  painter.setFont( font );

//  // draw labels in corners of page
//  painter.drawText( page, Qt::AlignTop    | Qt::AlignLeft, "QSimulate" );
//  painter.drawText( page, Qt::AlignBottom | Qt::AlignLeft, QString(getenv("USER")) );
//  painter.drawText( page, Qt::AlignBottom | Qt::AlignRight,
//                    QDateTime::currentDateTime().toString( Qt::DefaultLocaleShortDate ) );

//  // draw simulated landscape
//  page.adjust( w/20, h/20, -w/20, -h/20 );
////  m_scene->render( &painter, page );
//}

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
//    port->setReadBufferSize(1024);
    port->waitForBytesWritten(-1);
    if(port->isOpen())
        stopMeasure();
    else
    {
        if(port->open(QIODevice::ReadWrite))
        {
            pbMeasure->doMeasure = true;
            if(curentParam->workRegim == curentParam->regimAutoFreez)
            {
                QStandardItemModel *model;
                model = (QStandardItemModel*)pSampleTable->twMeas->model();
                model->setRowCount(0);
            }
            timer->start(100);
            countMeasure=0;
        }
    }
}

void mesurement::doTimer()
{
    QList <quint16> extremum;
    stMainParam mainParam;
    QByteArray baTmp, baTmp2;
    double x[2024], y[2024];
    quint16 kolvo = 0;

    if(port->isOpen())
    {
        timer->start(62);
        baTmp = port->readAll();
        baTmp2.clear();
//        qDebug()<<baTmp.length();
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
                switch(curentParam->workRegim)
                {
                case curentParam->regimAuto:
                    countMeasure++;
                    pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    if(countMeasure>=1)
                        stopMeasure();
                    break;
                case curentParam->regimAutoFreez:
                    countMeasure++;
                    pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    if(countMeasure>=8)
                        stopMeasure();
                    break;
                case curentParam->regimManual:
                    if(countMeasure==0)
                        pSampleTable->addSampleToTable(baTmp2, mainParam, true);
                    else
                        pSampleTable->addSampleToTable(baTmp2, mainParam, false);
                    countMeasure=1;
                    break;
                }
            }
        }
//        port->readAll();
        port->write("A", 1);
    }
}

void mesurement::stopMeasure()
{
    port->close();
    timer->start(1000);
    pbMeasure->doMeasure = false;
    pSampleTable->goToLastSample();
}
