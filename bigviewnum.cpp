#include "bigviewnum.h"
#include "ui_bigviewnum.h"

bigviewnum::bigviewnum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
}

bigviewnum::~bigviewnum()
{
    delete ui;
}
