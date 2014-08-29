#include "calculator_patient.h"
#include "ui_calculator_patient.h"
#include <QDebug>

calculator_patient::calculator_patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator_patient)
{
    ui->setupUi(this);
    bLeft = true;
    connect(ui->leK1, SIGNAL(editingFinished()),SLOT(RefreshK()));
    connect(ui->leK2, SIGNAL(editingFinished()),SLOT(RefreshK()));
    connect(ui->leACD_measure, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leAL_measure, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leAConst_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leACD_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leSF_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->pbSide, SIGNAL(clicked()), SLOT(ChangeSide()));
}

void calculator_patient::refreshPatientParam()
{
    quint16 id;
    id = ui->lePatientId->text().toUInt();
    QString str = QString("SELECT k1left,k2left,k1right,k2right,birth FROM patient WHERE id=%1;")
            .arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        if(sql.next())
        {
            patientParam.K1Left = sql.value(sql.record().indexOf("k1left")).toFloat();
            patientParam.K1Right = sql.value(sql.record().indexOf("k1right")).toFloat();
            patientParam.K2Left = sql.value(sql.record().indexOf("k2left")).toFloat();
            patientParam.K2Right = sql.value(sql.record().indexOf("k2right")).toFloat();
            patientParam.BirthDay = sql.value(sql.record().indexOf("birth")).toString();
            if(bLeft)
            {
                ui->leK1->setTextZero(QString("%1").arg(sql.value(sql.record().indexOf("k1left")).toFloat()));
                ui->leK2->setTextZero(QString("%1").arg(sql.value(sql.record().indexOf("k2left")).toFloat()));
            }
            else
            {
                ui->leK1->setTextZero(QString("%1").arg(sql.value(sql.record().indexOf("k1right")).toFloat()));
                ui->leK2->setTextZero(QString("%1").arg(sql.value(sql.record().indexOf("k2right")).toFloat()));
            }
            RefreshK();
        }
    }
}

void calculator_patient::refreshMeasure(stMeasureParam measureParam)
{
    ui->leAL_measure->setText(QString("%1").arg(measureParam.AL));
    ui->leACD_measure->setText(QString("%1").arg(measureParam.ACD));
    updateParam();
}


void calculator_patient::RefreshK()
{
    float fTmp;
    fTmp = (ui->leK1->text().toFloat()+ui->leK2->text().toFloat())/2;
    ui->leK->setTextZero(QString("%1").arg(fTmp));
    updateParam();
}

stPatientParam calculator_patient::getParam()
{
    stPatientParam stTmp;
    stTmp = patientParam;
    stTmp.id  =  ui->lePatientId->text().toUInt();
    stTmp.Name = ui->lePatientName->text();
    stTmp.K   =  ui->leK->text().toFloat();
    stTmp.ACD =  ui->leACD_measure->text().toFloat();
    stTmp.AL  =  ui->leAL_measure->text().toFloat();
    return stTmp;
}

stPersonalParam calculator_patient::getPersonalParam()
{
    stPersonalParam stTmp;
    stTmp.AConst = ui->leAConst_personal->text().toFloat();
    stTmp.ACD    = ui->leACD_personal->text().toFloat();
    stTmp.SF     = ui->leSF_personal->text().toFloat();
    return stTmp;
}

void calculator_patient::ChangeSide()
{
    bLeft = (!bLeft);
    refreshPatientParam();
    ui->pbSide->setText(bLeft?"OD":"OS");
}

void calculator_patient::setPatient(quint16 id, QString Patient, QString Doctor)
{
    ui->lePatientId->setText(QString("%1").arg(id));
    ui->lePatientName->setText(Patient);
    ui->leDoctorName->setText(Doctor);
}

void calculator_patient::updateParam()
{
    emit (refreshFormula());
}

calculator_patient::~calculator_patient()
{
    delete ui;
}
