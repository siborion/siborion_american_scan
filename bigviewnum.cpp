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
    ui->lAveAL_2->setText(QString("%1").arg(curentParam->measureAveAL,5,'f',2,'0'));
    ui->lDevAL_2->setText(QString("%1").arg(curentParam->measureDevAL,5,'f',2,'0'));

    ui->lAvgAcd_2->setText(QString("%1").arg(curentParam->measureAveACD,5,'f',2,'0'));
    ui->lAvgLt_2 ->setText(QString("%1").arg(curentParam->measureAveLT, 5,'f',2,'0'));
    ui->lAvgVit_2->setText(QString("%1").arg(curentParam->measureAveVIT,5,'f',2,'0'));

    ui->lDevAcd_2->setText(QString("%1").arg(curentParam->measureDevACD,5,'f',2,'0'));
    ui->lDevLt_2 ->setText(QString("%1").arg(curentParam->measureDevLT, 5,'f',2,'0'));
    ui->lDevVit_2->setText(QString("%1").arg(curentParam->measureDevVIT,5,'f',2,'0'));
}

