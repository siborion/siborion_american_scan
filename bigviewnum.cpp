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

void bigviewnum::setDisplay(double Avg, double AvgAcd, double AvgLt, double AvgVit, double Dev, double DevAcd, double DevLt, double DevVit)
{
    ui->lAveAL->setText(QString("%1").arg(Avg,4,'f',2));
    ui->lDevAL->setText(QString("%1").arg(Dev,4,'f',2));

    ui->lAvgAcd->setText(QString("%1").arg(AvgAcd,4,'f',2));
    ui->lAvgLt ->setText(QString("%1").arg(AvgLt, 4,'f',2));
    ui->lAvgVit->setText(QString("%1").arg(AvgVit,4,'f',2));

    ui->lDevAcd->setText(QString("%1").arg(DevAcd,4,'f',2));
    ui->lDevLt ->setText(QString("%1").arg(DevLt, 4,'f',2));
    ui->lDevVit->setText(QString("%1").arg(DevVit,4,'f',2));

}

void bigviewnum::setDisplay(double Al)
{
//    ui->lAlCur->setText(QString("%1").arg(Al));
}
