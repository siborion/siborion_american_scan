#include "bigviewnumcur.h"
#include "ui_bigviewnumcur.h"
#include <qDebug>

bigviewnumcur::bigviewnumcur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnumcur)
{
    QDate curData;
    curData=QDate::currentDate();
    curentParam = CurentParam::instanse();
    ui->setupUi(this);
    ui->lData->setText(curData.toString("dd.MM.yyyy"));

    curentParam->patientMaper.addMapping(ui->lFioPatient, 1);
    curentParam->patientMaper.addMapping(ui->lFioDoctor,  2);
}

bigviewnumcur::~bigviewnumcur()
{
    delete ui;
}

void bigviewnumcur::setDisplay(double AL, double ACD, double LT, double VIT)
{
    ui->lCurAL->setText(QString("%1").arg(AL,4,'f',2));
    ui->lCurACD->setText(QString("%1").arg(ACD,4,'f',2));
    ui->lCurLT->setText(QString("%1").arg(LT,4,'f',2));
    ui->lCurVIT->setText(QString("%1").arg(VIT,4,'f',2));
}

//void bigviewnumcur::setPatient(QString FIO)
//{
//    ui->lFioPatient->setText(FIO);
//}

//void bigviewnumcur::setDoctor(QString FIO)
//{
//    ui->lFioDoctor->setText(FIO);
//}

void bigviewnumcur::changeEye(quint8 val)
{
    if(val==0)
        ui->lYeas->setText("OD");
    else
        ui->lYeas->setText("OS");
}

