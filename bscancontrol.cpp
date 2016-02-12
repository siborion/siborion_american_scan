#include "bscancontrol.h"
#include "ui_bscancontrol.h"

BScanControl::BScanControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanControl)
{
    ui->setupUi(this);
}

BScanControl::~BScanControl()
{
    delete ui;
}
