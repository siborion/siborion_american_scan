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

    pScena = new scena(500, buf);

    ui->horizontalLayout->addWidget(bScanTools);
    ui->horizontalLayout->addWidget(pScena);
    ui->horizontalLayout->addWidget(bScanControl);

    connect(bScanTools, SIGNAL(doScan()),           SLOT(doStart()));
    connect(bScanTools, SIGNAL(doStop()),           SLOT(doStop()));
    connect(bScanTools, SIGNAL(doOS()),             SLOT(setRun()));
    connect(timer,      SIGNAL(timeout()),          SLOT(scenaRefr()));
    connect(timerSec,   SIGNAL(timeout()),          SLOT(doSec()));

//    timer->start();
//    timerSec->start();
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

void Bscan::doStart()
{
    bScanHard->process();
    timer->start();
    timerSec->start();
}

void Bscan::doStop()
{
    bScanHard->close();
    timer->stop();
    timerSec->stop();
}

void Bscan::setRun()
{
    run ^= 1;
    bScanHard->setRun(run);
}

Bscan::~Bscan()
{
    delete ui;
}
