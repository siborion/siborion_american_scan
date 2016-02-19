#include "bscan.h"
#include "ui_bscan.h"
#include <QDebug>

Bscan::Bscan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bscan)
{
    ui->setupUi(this);

    timer        = new QTimer();
    timer->setInterval(50);

    timerSec     = new QTimer();
    timerSec->setInterval(1000);

    bScanTools   = new BScanTools();
    bScanControl = new BScanControl();
    bScanHard = new BScanHard();
    buf = bScanHard->getBuf();
//    qDebug()<<buf[0]<<buf[1]<<buf[2];

    pScena = new scena(500, buf);

    ui->horizontalLayout->addWidget(bScanTools);
    ui->horizontalLayout->addWidget(pScena);
    ui->horizontalLayout->addWidget(bScanControl);

    connect(bScanTools, SIGNAL(doScan()), bScanHard, SLOT(process()));
    connect(bScanTools, SIGNAL(doStop()), bScanHard, SLOT(close()));
    connect(bScanTools, SIGNAL(doOS()),              SLOT(softRun()));
    connect(timer,      SIGNAL(timeout()),           SLOT(scenaRefr()));
    connect(timerSec,   SIGNAL(timeout()),           SLOT(doSec()));

    timer->start();
    timerSec->start();
}

void Bscan::scenaRefr()
{
    bScanHard->getBuf();
    pScena->refr();
    fps++;
}

void Bscan::doSec()
{
    bScanTools->setFps(fps);
    fps = 0;
}

void Bscan::softRun()
{
    run ^= 1;
    bScanHard->softRun(run);
    qDebug()<<"softRun"<<run;
}


Bscan::~Bscan()
{
    delete ui;
}
