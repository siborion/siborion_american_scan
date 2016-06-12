#include "calculator_patient.h"
#include "ui_calculator_patient.h"
#include "func.h"
#include <QDebug>

calculator_patient::calculator_patient(QWidget *parent, CurParam *link) :
    QWidget(parent),
    ui(new Ui::calculator_patient)
{
    ui->setupUi(this);
    curParam = link;

    softUpdate = false;



    foreach (QObject *ob1, this->children())
    {
        foreach (QObject *ob2, ob1->children())
        {
            QLabel *la = dynamic_cast<QLabel*>(ob2);
            if(la) la->setFont(getFont(10, true));
            QLineEdit *le = dynamic_cast<QLineEdit*>(ob2);
            if(le) le->setFont(getFont(10, false));
        }
        QLabel *la = dynamic_cast<QLabel*>(ob1);
        if(la) la->setFont(getFont(10, true));
        QLineEdit *le = dynamic_cast<QLineEdit*>(ob1);
        if(le) le->setFont(getFont(10, false));
    }

    bLeft = true;
    connect(ui->leK1, SIGNAL(editingFinished()),SLOT(RefreshK()));
    connect(ui->leK2, SIGNAL(editingFinished()),SLOT(RefreshK()));
    connect(ui->leACD_measure, SIGNAL(editingFinished()), SLOT(refreshAlACD()));
    connect(ui->leAL_measure, SIGNAL(editingFinished()), SLOT(refreshAlACD()));
    connect(ui->leAConst_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leACD_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leSF_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->leRx_personal, SIGNAL(editingFinished()), SLOT(updateParam()));
    connect(ui->pbSide, SIGNAL(clicked()), SLOT(ChangeSide()));
}

void calculator_patient::refreshAlACD()
{
    if(softUpdate)
        return;
    softUpdate = true;
    curParam->ACD    = ui->leACD_measure->text().toDouble();
    curParam->ALave  = ui->leAL_measure->text().toDouble();
    emit (refreshFormula());
    softUpdate = false;
}

void calculator_patient::refreshPatientParam()
{
    if(softUpdate)
        return;
    softUpdate = true;
    patientParam.K1Left  = curParam->k1left;
    patientParam.K1Right = curParam->k1right;
    patientParam.K2Left  = curParam->k2left;
    patientParam.K2Right = curParam->k2right;
    if(curParam->regimSide == REGIM::OD)
    {
        ui->leK1->setTextZero(QString("%1").arg(curParam->k1left));
        ui->leK2->setTextZero(QString("%1").arg(curParam->k2left));
        ui->pbSide->setText("OD");
    }
    else
    {
        ui->leK1->setTextZero(QString("%1").arg(curParam->k1right));
        ui->leK2->setTextZero(QString("%1").arg(curParam->k2right));
        ui->pbSide->setText("OS");
    }
    ui->lePatientId->setText(QString("%1").arg(curParam->patientId));
    ui->lePatientName->setText(curParam->patientName);
    ui->leDoctorName->setText(curParam->doctorName);
    ui->leACD_measure->setText(QString("%1").arg(curParam->ACD));
    ui->leAL_measure->setTextZero(QString("%1").arg(curParam->ALave));
    RefreshK();
    softUpdate = false;
    ui->lePatientId->setFocus();
}



void calculator_patient::refreshMeasure()
{
//!!    ui->leAL_measure->setText(QString("%1").arg(curentParam->measureAveAL));
//!!    ui->leACD_measure->setText(QString("%1").arg(curentParam->measureAveACD));
//    updateParam();
}

void calculator_patient::RefreshK()
{
    float fTmp;
    fTmp = (ui->leK1->text().toFloat()+ui->leK2->text().toFloat())/2;
    ui->leK->setTextZero(QString("%1").arg(fTmp));
    curParam->K = fTmp;
    emit (refreshFormula());
}

//stPatientParam calculator_patient::getParam()
//{
//    stPatientParam stTmp;
//    stTmp = patientParam;
//    stTmp.id  =  ui->lePatientId->text().toUInt();
//    stTmp.Name = ui->lePatientName->text();
//    stTmp.K   =  ui->leK->text().toFloat();
//    stTmp.ACD =  ui->leACD_measure->text().toFloat();
//    stTmp.AL  =  ui->leAL_measure->text().toFloat();
//    return stTmp;
//}

stPersonalParam calculator_patient::getPersonalParam()
{
    stPersonalParam stTmp;
    stTmp.AConst = ui->leAConst_personal->text().toFloat();
    stTmp.ACD    = ui->leACD_personal->text().toFloat();
    stTmp.SF     = ui->leSF_personal->text().toFloat();
    curParam->Rx = stTmp.Rx     = ui->leRx_personal->text().toFloat();
    return stTmp;
}

void calculator_patient::ChangeSide()
{
    if(curParam->regimSide==REGIM::OD)
    {
        curParam->regimSide = REGIM::OS;
        ui->pbSide->setText("OS");
    }
    else
    {
        curParam->regimSide = REGIM::OD;
        ui->pbSide->setText("OD");
    }
    emit changeSideCalculator();
    updateParam();
}

void calculator_patient::setPatient(quint16 id, QString Patient, QString Doctor)
{
//    ui->lePatientId->setText(QString("%1").arg(id));
//    ui->lePatientName->setText(Patient);
//    ui->leDoctorName->setText(Doctor);
}

void calculator_patient::updateParam()
{
    double dTmp;
    QObject* sender = const_cast<QObject*>(QObject::sender());
    if(sender)
    {
        if(sender->objectName()=="leAConst_personal")
        {
            dTmp =  ui->leAConst_personal->text().toDouble();
            dTmp =  (0.5663 * dTmp) - 65.60;
            ui->leSF_personal->setText(QString("%1").arg(dTmp));

            dTmp =  ui->leAConst_personal->text().toDouble();
            dTmp = (0.5663* dTmp - 65.60 +3.595) / 0.9704;
            ui->leACD_personal->setText(QString("%1").arg(dTmp));
        }
        if(sender->objectName()=="leACD_personal")
        {
            dTmp = ui->leACD_personal->text().toDouble();
            dTmp = (0.9704 * dTmp) - 3.595;
            ui->leSF_personal->setText(QString("%1").arg(dTmp));

            dTmp = ui->leACD_personal->text().toDouble();
            dTmp = (0.9704 * dTmp - 3.595 + 65.60) / 0.5663;
            ui->leAConst_personal->setText(QString("%1").arg(dTmp));
        }
        if(sender->objectName()=="leSF_personal")
        {
            dTmp = ui->leSF_personal->text().toDouble();
            dTmp += 65.60;
            dTmp /= 0.5663;
            ui->leAConst_personal->setText(QString("%1").arg(dTmp));

            dTmp = ui->leSF_personal->text().toDouble();
            dTmp += 3.595;
            dTmp /= 0.9704;
            ui->leACD_personal->setText(QString("%1").arg(dTmp));
        }
    emit (refreshFormula());
    }
}

void calculator_patient::updatePatient()
{
    refreshPatientParam();
    emit (refreshFormula());
}

calculator_patient::~calculator_patient()
{
    delete ui;
}
