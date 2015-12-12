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
    ui->leData->setText(curData.toString("dd.MM.yyyy"));

    curentParam->patientMaper.addMapping(ui->lFioPatient, 1);
    curentParam->patientMaper.addMapping(ui->lFioDoctor,  2);
    curentParam->patientMaper.addMapping(ui->leSide, 7);
}

bigviewnumcur::~bigviewnumcur()
{
    delete ui;
}

void bigviewnumcur::setDisplay(double AL, double ACD, double LT, double VIT)
{
    ui->lCurAL->setText(QString("%1").arg(AL,5,'f',2,'0'));
    ui->lCurACD->setText(QString("%1").arg(ACD,5,'f',2,'0'));
    ui->lCurLT->setText(QString("%1").arg(LT,5,'f',2,'0'));
    ui->lCurVIT->setText(QString("%1").arg(VIT,5,'f',2,'0'));
}

//void bigviewnumcur::setPatient(QString FIO)
//{
//    ui->lFioPatient->setText(FIO);
//}

//void bigviewnumcur::setDoctor(QString FIO)
//{
//    ui->lFioDoctor->setText(FIO);
//}

//void bigviewnumcur::changeEye(quint8 val)
//{
//    if(val==0)
//        ui->lYeas->setText("OD");
//    else
//        ui->lYeas->setText("OS");
//}

