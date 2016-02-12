#include "bscan.h"
#include "ui_bscan.h"

Bscan::Bscan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bscan)
{
    ui->setupUi(this);
    pScena = new scena(600);
    bScanTools   = new BScanTools();
    bScanControl = new BScanControl();
    bScanUSB = new BScanUSB();

    ui->horizontalLayout->addWidget(bScanTools);
    ui->horizontalLayout->addWidget(pScena);
    ui->horizontalLayout->addWidget(bScanControl);
}

Bscan::~Bscan()
{
    delete ui;
}
