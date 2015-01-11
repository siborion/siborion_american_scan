#include "bigviewnumcur.h"
#include "ui_bigviewnumcur.h"
#include <qDebug>

Bigviewnumcur::Bigviewnumcur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bigviewnumcur)
{
    QDate curData;
    curData=QDate::currentDate();
    ui->setupUi(this);
    ui->leData->setText(curData.toString("dd.MM.yyyy"));
}

Bigviewnumcur::~Bigviewnumcur()
{
    delete ui;
}

void Bigviewnumcur::setDisplay(stMeasureParam *curParam)
{
    ui->lCurAL->setText(QString("%1").arg (curParam->AL,5,'f',2,'0'));
    ui->lCurACD->setText(QString("%1").arg(curParam->ACD,5,'f',2,'0'));
    ui->lCurLT->setText(QString("%1").arg (curParam->LT,5,'f',2,'0'));
    ui->lCurVIT->setText(QString("%1").arg(curParam->VIT,5,'f',2,'0'));
}

