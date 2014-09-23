#include "bigviewnum.h"
#include "ui_bigviewnum.h"
#include <qDebug>

bigviewnum::bigviewnum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
    curentParam = CurentParam::instanse();
    setMinimumSize(200,200);

    curentParam->measureParamMaper.addMapping(ui->lAveAL_2, 0,"text");
    curentParam->measureParamMaper.addMapping(ui->lAvgAcd_2,1,"text");

}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay(double Avg, double AvgAcd, double AvgLt, double AvgVit, double Dev, double DevAcd, double DevLt, double DevVit)
{
//    ui->lAveAL_2->setText(QString("%1").arg(Avg,4,'f',2));
    ui->lDevAL_2->setText(QString("%1").arg(Dev,4,'f',2));

//    ui->lAvgAcd_2->setText(QString("%1").arg(AvgAcd,4,'f',2));
    ui->lAvgLt_2 ->setText(QString("%1").arg(AvgLt, 4,'f',2));
    ui->lAvgVit_2->setText(QString("%1").arg(AvgVit,4,'f',2));

    ui->lDevAcd_2->setText(QString("%1").arg(DevAcd,4,'f',2));
    ui->lDevLt_2 ->setText(QString("%1").arg(DevLt, 4,'f',2));
    ui->lDevVit_2->setText(QString("%1").arg(DevVit,4,'f',2));

}

void bigviewnum::setDisplay(double Al)
{
//    ui->lAlCur->setText(QString("%1").arg(Al));
}
