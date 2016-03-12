#include "bscantabloa.h"
#include "ui_bscantabloa.h"

BScanTabloA::BScanTabloA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanTabloA)
{
    ui->setupUi(this);
    this->repaint();
}

BScanTabloA::~BScanTabloA()
{
    delete ui;
}
