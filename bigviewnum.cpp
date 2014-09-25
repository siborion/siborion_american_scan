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

//    curentParam->measureParamMaper.addMapping(ui->lAveAL_2, 0,"text");
//    curentParam->measureParamMaper.addMapping(ui->lAvgAcd_2,1,"text");

}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay()
{
    ui->lAveAL_2->setText(QString("%1").arg(curentParam->measureAveAL,4,'f',2));
    ui->lDevAL_2->setText(QString("%1").arg(curentParam->measureDevAL,4,'f',2));

    ui->lAvgAcd_2->setText(QString("%1").arg(curentParam->measureAveACD,4,'f',2));
    ui->lAvgLt_2 ->setText(QString("%1").arg(curentParam->measureAveLT, 4,'f',2));
    ui->lAvgVit_2->setText(QString("%1").arg(curentParam->measureAveVIT,4,'f',2));

    ui->lDevAcd_2->setText(QString("%1").arg(curentParam->measureDevACD,4,'f',2));
    ui->lDevLt_2 ->setText(QString("%1").arg(curentParam->measureDevLT, 4,'f',2));
    ui->lDevVit_2->setText(QString("%1").arg(curentParam->measureDevVIT,4,'f',2));

}

