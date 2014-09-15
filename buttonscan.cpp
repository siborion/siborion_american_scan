#include "buttonscan.h"
#include "ui_buttonscan.h"

ButtonScan::ButtonScan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonScan)
{
    ui->setupUi(this);
}

ButtonScan::~ButtonScan()
{
    delete ui;
}
