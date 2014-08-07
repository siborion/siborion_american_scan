#include "calculator_patient.h"
#include "ui_calculator_patient.h"

calculator_patient::calculator_patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator_patient)
{
    ui->setupUi(this);
    bLeft = true;
    connect(ui->leK1, SIGNAL(editingFinished()),SLOT(RefreshK()));
    connect(ui->pbSide, SIGNAL(clicked()), SLOT(ChangeSide()));
}

void calculator_patient::refreshPatientParam(quint16 id)
{
    curId = id;
    QString str = QString("SELECT k1left, k2left, k1right, k2right FROM patient WHERE id=%1;")
            .arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        if(sql.next())
        {
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

void calculator_patient::RefreshK()
{
    ui->leK->setTextZero(QString("%1").arg((ui->leK1->text().toFloat()+ui->leK2->text().toFloat())/2));
}

void calculator_patient::ChangeSide()
{
    bLeft = (!bLeft);
    refreshPatientParam(curId);
    ui->pbSide->setText(bLeft?"OD":"OS");
}

void calculator_patient::setPatient(quint16 id, QString Patient, QString Doctor)
{
    ui->lePatientId->setText(QString("%1").arg(id));
    ui->lePatientName->setText(Patient);
    ui->leDoctorName->setText(Doctor);

}

calculator_patient::~calculator_patient()
{
    delete ui;
}
