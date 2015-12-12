#include "velosity.h"
#include "ui_velosity.h"

Velosity::Velosity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Velosity)
{
    ui->setupUi(this);
    pbMeasure = new ScanButton();
    ui->gridLayout_2->addWidget(pbMeasure,0,3,2,1);
    connect(pbMeasure,SIGNAL(pressed()),SLOT(doScan()));
}

void Velosity::doScan()
{
    emit pressed();
}

Velosity::~Velosity()
{
    delete ui;
}
