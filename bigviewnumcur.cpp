#include "bigviewnumcur.h"
#include "ui_bigviewnumcur.h"
#include <qDebug>

Bigviewnumcur::Bigviewnumcur(QWidget *parent, CurParam *link) :
    QWidget(parent),
    ui(new Ui::Bigviewnumcur)
{
    QDate curData;
    curParam = link;
    curData=QDate::currentDate();
    ui->setupUi(this);
    ui->leData->setText(curData.toString("dd.MM.yyyy"));
}

Bigviewnumcur::~Bigviewnumcur()
{
    delete ui;
}

void Bigviewnumcur::setDisplay(stMeasureParam *link)
{
    ui->lCurAL->setText(QString("%1").arg (link->ALave , 5,'f',2,'0'));
    ui->lCurACD->setText(QString("%1").arg(link->ACD,4,'f',2,'0'));
    ui->lCurLT->setText(QString("%1").arg (link->LT, 4,'f',2,'0'));
    ui->lCurVIT->setText(QString("%1").arg(link->VIT,5,'f',2,'0'));
}

void Bigviewnumcur::setRegim()
{
    bool bAuto, bCataract, bVal;
    bAuto = (curParam->regimMeasure  != REGIM::MANUAL);
    bCataract = (curParam->regimCataract == REGIM::CATARACT);

    ui->lCurACD->setVisible(bAuto);
    ui->lCurLT->setVisible(bAuto);
    ui->lCurVIT->setVisible(bAuto);
    ui->lACD->setVisible(bAuto);
    ui->lLT->setVisible(bAuto);
    ui->lVIT->setVisible(bAuto);
    ui->lAL->setText(bAuto?"AL":"Dist");

    bVal = (curParam->regimSide == REGIM::OD);
    ui->leSide->setText(bVal?"OD":"OS");
}

void Bigviewnumcur::updatePatient()
{
    ui->lFioPatient->setText(curParam->patientName);
    ui->lFioDoctor->setText (curParam->doctorName);

    ui->lCurAL->setText(QString("%1").arg (0,5,'f',2,'0'));
    ui->lCurACD->setText(QString("%1").arg(0,4,'f',2,'0'));
    ui->lCurLT->setText(QString("%1").arg (0,4,'f',2,'0'));
    ui->lCurVIT->setText(QString("%1").arg(0,5,'f',2,'0'));
}
