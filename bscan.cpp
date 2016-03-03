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

    bScanTools   = new BScanTools();
    bScanControl = new BScanControl();
    bScanHard = new BScanHard();
    buf = bScanHard->getBuf();

    pScena = new scena(scenaSize, buf);

    ui->horizontalLayout->addWidget(bScanTools);
    ui->horizontalLayout->addWidget(pScena);
    ui->horizontalLayout->addWidget(bScanControl);

    connect(bScanTools, SIGNAL(doScan()),           SLOT(doStart()));
    connect(bScanTools, SIGNAL(doStop()),           SLOT(doStop()));
    connect(bScanTools, SIGNAL(doOS()),             SLOT(setRun()));
    connect(bScanTools, SIGNAL(doEdit(CUR_EDIT,bool)), pScena, SLOT(doEdit(CUR_EDIT,bool)));

    connect(timer,      SIGNAL(timeout()),          SLOT(scenaRefr()));
    connect(timerSec,   SIGNAL(timeout()),          SLOT(doSec()));

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
//    run ^= 1;
//    bScanHard->setRun(run);
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
