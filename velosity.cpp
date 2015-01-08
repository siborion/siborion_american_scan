#include "velosity.h"
#include "ui_velosity.h"
#include <qdebug.h>

Velosity::Velosity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Velosity)
{
    ui->setupUi(this);
    pbMeasure = new ScanButton();
    ui->gridLayout_2->addWidget(pbMeasure,0,3,2,1);
    connect(pbMeasure,SIGNAL(doScan(bool*)),SLOT(doScanSlot(bool*)));
}

void Velosity::doScanSlot(bool *doMeasure)
{
    emit doScan(doMeasure);
}

Velosity::~Velosity()
{
    delete ui;
}
