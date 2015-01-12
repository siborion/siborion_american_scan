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
    ui->lCurAL->setText(QString("%1").arg (link->AL,5,'f',2,'0'));
    ui->lCurACD->setText(QString("%1").arg(link->ACD,5,'f',2,'0'));
    ui->lCurLT->setText(QString("%1").arg (link->LT,5,'f',2,'0'));
    ui->lCurVIT->setText(QString("%1").arg(link->VIT,5,'f',2,'0'));
}

void Bigviewnumcur::setRegim()
{
    bool bVal;
    bVal = (curParam->regimMeasure  != REGIM::MANUAL);
    ui->lCurACD->setVisible(bVal);
    ui->lCurLT->setVisible(bVal);
    ui->lCurVIT->setVisible(bVal);
    ui->lACD->setVisible(bVal);
    ui->lLT->setVisible(bVal);
    ui->lVIT->setVisible(bVal);
    ui->lAL->setText(bVal?"AL":"Dist");

    bVal = (curParam->regimSide == REGIM::OD);
    ui->leSide->setText(bVal?"OD":"OS");
}

void Bigviewnumcur::updatePatient()
{
    ui->lFioPatient->setText(curParam->patientName);
    ui->lFioDoctor->setText (curParam->doctorName);
}
