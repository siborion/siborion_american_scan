#include "measure.h"
#include "ui_measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Measure)
{
    ui->setupUi(this);
}

Measure::~Measure()
{
    delete ui;
}
