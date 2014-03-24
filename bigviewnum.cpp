#include "bigviewnum.h"
#include "ui_bigviewnum.h"
#include <qDebug>

bigviewnum::bigviewnum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
    setMinimumSize(200,200);
}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay(double Al, double Avg, double Dev)
{
    ui->lAlCur->setText(QString("%1").arg(Al));
    ui->lAlAvg->setText(QString("%1").arg(Avg));
    ui->lAlDev->setText(QString("%1").arg(Dev));
}

void bigviewnum::setDisplay(double Al)
{
    ui->lAlCur->setText(QString("%1").arg(Al));
}
