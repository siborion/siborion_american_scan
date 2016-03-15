#include "bscan.h"
#include "ui_bscan.h"
#include <QDebug>
#include <QSettings>

Bscan::Bscan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bscan)
{
    quint16 scenaSize;

    QSettings settings("scan.ini", QSettings::IniFormat);
    settings.beginGroup("b-scan");
    scenaSize = settings.value("size", 500).toUInt();
    settings.endGroup();

    if(scenaSize>=900)
        scenaSize = 900;

    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);

    timer        = new QTimer();
    timer->setInterval(50);

    timerSec     = new QTimer();
    timerSec->setInterval(1000);

    bScanTabloA = new BScanTabloA();
//    bScanTabloA->setMinimumHeight(150);
//    bScanTabloA->setMaximumHeight(150);
        bScanTabloA->setMinimumSize(150,150);
        bScanTabloA->setMaximumSize(150,150);


    run = false;

    bScanTools   = new BScanTools();
    bScanControl = new BScanControl();
    bScanHard = new BScanHard();
    buf = bScanHard->getBuf();

    pScena = new scena(scenaSize, buf);

    ui->gridLayout_2->addWidget(bScanTools,  0,0,2,1);
    ui->gridLayout_2->addWidget(pScena,      0,1,2,1);
//    ui->gridLayout_2->addWidget(bScanTabloA, 0,1,1,1);
    ui->gridLayout_2->addWidget(bScanControl,0,2,2,1);

    buf = bScanHard->getBuf();
    bScanControl->setBuf(buf);
    bScanControl->setBuf(buf);
    bScanControl->setBuf(buf);
    bScanControl->setBuf(buf);

    connect(bScanTools, SIGNAL(doScan()),           SLOT(doStart()));
    connect(bScanTools, SIGNAL(doStop()),           SLOT(doStop()));
    connect(bScanTools, SIGNAL(doOS()),             SLOT(setRun()));
    connect(bScanTools, SIGNAL(doEdit(CUR_EDIT,bool)), pScena, SLOT(doEdit(CUR_EDIT,bool)));

    connect(timer,      SIGNAL(timeout()),          SLOT(scenaRefr()));
    connect(timerSec,   SIGNAL(timeout()),          SLOT(doSec()));

    connect(pScena, SIGNAL(sgUpdateArray(QString*)),   bScanControl, SLOT(slSetArray(QString*)));
    connect(pScena, SIGNAL(sgUpdateArrow(QString*)),   bScanControl, SLOT(slSetArrow(QString*)));
    connect(pScena, SIGNAL(sgUpdateCaliper(QString*)), bScanControl, SLOT(slSetCaliper(QString*)));

    connect(bScanControl, SIGNAL(sgUpdateArray(QString*)),   pScena,   SLOT(setArray(QString*)));
    connect(bScanControl, SIGNAL(sgUpdateArrow(QString*)),   pScena,   SLOT(setArrow(QString*)));
    connect(bScanControl, SIGNAL(sgUpdateCaliper(QString*)), pScena,   SLOT(setCaliper(QString*)));

    timer->start();
    timerSec->start();
}

void Bscan::scenaRefr()
{
    if(run)
    {
        buf = bScanHard->getBuf();
        bScanControl->setBuf(buf);
    }
    else
        buf = bScanControl->getBuf();
if(buf)
    pScena->refr(buf);
    fps++;
}

void Bscan::doSec()
{
    bScanTools->setFps(fps);
    fps = 0;
}

void Bscan::doStart()
{
    qDebug()<<"start";
    bScanHard->process();
    timer->start();
    timerSec->start();
    run = true;
}

void Bscan::doStop()
{
    qDebug()<<"stop";
    bScanHard->close();
//    timer->stop();
//    timerSec->stop();
    run = false;
}

void Bscan::setRun()
{
    QString sTmp;
    sTmp = pScena->getArrowString();
    pScena->setArrow(&sTmp);

    sTmp = pScena->getArrayString();
    pScena->setArray(&sTmp);

    sTmp = pScena->getCaliperString();
    pScena->setCaliper(&sTmp);

}

void Bscan::keyPressEvent(QKeyEvent *kEvent)
{
    pScena->keyPressEvent(kEvent);
}

void Bscan::keyReleaseEvent(QKeyEvent *kEvent)
{
    pScena->keyReleaseEvent(kEvent);
}

Bscan::~Bscan()
{
    delete ui;
}
