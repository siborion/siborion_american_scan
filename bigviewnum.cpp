#include "bigviewnum.h"
#include "ui_bigviewnum.h"
//#include <qDebug>

bigviewnum::bigviewnum(QWidget *parent, CurParam *link) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
    curParam = link;
}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay(stAverageParam *averageParam)
{
    ui->lAvgAL_2->setText(QString("%1").arg(averageParam->ALave,     5,'f',2,'0'));
    ui->lDevAL_2->setText(QString("%1").arg(averageParam->ALavediv,  4,'f',2,'0'));
    ui->lAvgAcd_2->setText(QString("%1").arg(averageParam->ACD,   4,'f',2,'0'));
    ui->lDevAcd_2->setText(QString("%1").arg(averageParam->ACDdiv,4,'f',2,'0'));
    ui->lAvgLt_2 ->setText(QString("%1").arg(averageParam->LT,    4,'f',2,'0'));
    ui->lDevLt_2 ->setText(QString("%1").arg(averageParam->LTdiv, 4,'f',2,'0'));
    ui->lAvgVit_2->setText(QString("%1").arg(averageParam->VIT,   5,'f',2,'0'));
    ui->lDevVit_2->setText(QString("%1").arg(averageParam->VITdiv,4,'f',2,'0'));
    curParam->ALave  = averageParam->ALave;
    curParam->ACD = averageParam->ACD;
}

void bigviewnum::setRegim()
{
    bool bAuto, bCataract;
    bAuto = (curParam->regimMeasure  != REGIM::MANUAL);
    bCataract = (curParam->regimCataract == REGIM::CATARACT);
    ui->lAveACD->setVisible(bAuto && bCataract);
    ui->lAveLT->setVisible (bAuto && bCataract);
    ui->lAveVIT->setVisible(bAuto && bCataract);
    ui->lAvgAcd_2->setVisible(bAuto && bCataract);
    ui->lDevAcd_2->setVisible(bAuto && bCataract);
    ui->lAvgLt_2 ->setVisible(bAuto && bCataract);
    ui->lDevLt_2 ->setVisible(bAuto && bCataract);
    ui->lAvgVit_2->setVisible(bAuto && bCataract);
    ui->lDevVit_2->setVisible(bAuto && bCataract);
    ui->lStdACD->setVisible  (bAuto && bCataract);
    ui->lStdLT->setVisible   (bAuto && bCataract);
    ui->lStdVIT->setVisible  (bAuto && bCataract);
    ui->lAveAL->setText(bAuto?"AL":"Dist");
    ui->lStdAL->setText(bAuto?"AL":"Dist");
}

void bigviewnum::clearAll()
{
    ui->lAvgAL_2->setText(QString("%1").arg(0, 5,'f',2,'0'));
    ui->lDevAL_2->setText(QString("%1").arg(0, 4,'f',2,'0'));
    ui->lAvgAcd_2->setText(QString("%1").arg(0,4,'f',2,'0'));
    ui->lDevAcd_2->setText(QString("%1").arg(0,4,'f',2,'0'));
    ui->lAvgLt_2 ->setText(QString("%1").arg(0,4,'f',2,'0'));
    ui->lDevLt_2 ->setText(QString("%1").arg(0,4,'f',2,'0'));
    ui->lAvgVit_2->setText(QString("%1").arg(0,5,'f',2,'0'));
    ui->lDevVit_2->setText(QString("%1").arg(0,4,'f',2,'0'));
    curParam->ALave  = 0;
    curParam->ACD = 0;
}
