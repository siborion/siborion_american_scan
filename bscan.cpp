#include "bscan.h"
#include "ui_bscan.h"
#include <QDebug>

Bscan::Bscan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bscan)
{
    ui->setupUi(this);

    bScanTools   = new BScanTools();
    bScanControl = new BScanControl();
    bScanHard = new BScanHard();
    buf = bScanHard->getBuf();
    qDebug()<<buf[0]<<buf[1]<<buf[2];

    pScena = new scena(600, buf);

    ui->horizontalLayout->addWidget(bScanTools);
    ui->horizontalLayout->addWidget(pScena);
    ui->horizontalLayout->addWidget(bScanControl);



    connect(bScanTools, SIGNAL(doScan()), bScanHard, SLOT(process()));
}

Bscan::~Bscan()
{
    delete ui;
}
