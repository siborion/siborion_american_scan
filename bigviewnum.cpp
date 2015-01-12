#include "bigviewnum.h"
#include "ui_bigviewnum.h"
#include <qDebug>

bigviewnum::bigviewnum(QWidget *parent, CurParam *link) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
    curParam = link;
    //    curentParam = CurentParam::instanse();
    //    setMinimumSize(200,200);

    //    curentParam->measureParamMaper.addMapping(ui->lAveAL_2, 0,"text");
    //    curentParam->measureParamMaper.addMapping(ui->lAvgAcd_2,1,"text");

}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay(stAverageParam *averageParam)
{
    ui->lAvgAL_2->setText(QString("%1").arg(averageParam->AL,5,'f',2,'0'));
    ui->lDevAL_2->setText(QString("%1").arg(averageParam->ALdiv,5,'f',2,'0'));

    ui->lAvgAcd_2->setText(QString("%1").arg(averageParam->ACD,5,'f',2,'0'));
    ui->lDevAcd_2->setText(QString("%1").arg(averageParam->ACDdiv,5,'f',2,'0'));

    ui->lAvgLt_2 ->setText(QString("%1").arg(averageParam->LT, 5,'f',2,'0'));
    ui->lDevLt_2 ->setText(QString("%1").arg(averageParam->LTdiv, 5,'f',2,'0'));

    ui->lAvgVit_2->setText(QString("%1").arg(averageParam->VIT,5,'f',2,'0'));
    ui->lDevVit_2->setText(QString("%1").arg(averageParam->VITdiv,5,'f',2,'0'));

    curParam->AL  = averageParam->AL;
    curParam->ACD = averageParam->ACD;
}

void bigviewnum::setRegim()
{
    bool bVal;
    bVal = (curParam->regimMeasure  != REGIM::MANUAL);
    ui->lAveACD->setVisible(bVal);
    ui->lAveLT->setVisible(bVal);
    ui->lAveVIT->setVisible(bVal);
    ui->lAvgAcd_2->setVisible(bVal);
    ui->lDevAcd_2->setVisible(bVal);
    ui->lAvgLt_2 ->setVisible(bVal);
    ui->lDevLt_2 ->setVisible(bVal);
    ui->lAvgVit_2->setVisible(bVal);
    ui->lDevVit_2->setVisible(bVal);
    ui->lStdACD->setVisible(bVal);
    ui->lStdLT->setVisible(bVal);
    ui->lStdVIT->setVisible(bVal);
    ui->lAveAL->setText(bVal?"AL":"Dist");
    ui->lStdAL->setText(bVal?"AL":"Dist");
}


