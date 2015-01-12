#ifndef CALCULATOR_PATIENT_H
#define CALCULATOR_PATIENT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include "curparam.h"
#include "typedef.h"

namespace Ui {
class calculator_patient;
}

class calculator_patient : public QWidget
{
    Q_OBJECT

public:
    explicit calculator_patient(QWidget *parent = 0, CurParam *link = 0);
    ~calculator_patient();
    Ui::calculator_patient *ui;

private:

    stPatientParam patientParam;
    CurParam *curParam;
    bool softUpdate;

public:
    void setPatient(quint16 id, QString Patient, QString Doctor);
//    double K, AL_measure, ACD_measure;
    bool bLeft;
//    stPatientParam getParam();
    stPersonalParam getPersonalParam();
//    quint16 curId;
    void refreshMeasure();
    void updatePatient();

private slots:
    void RefreshK();
    void ChangeSide();
    void updateParam();
    void refreshPatientParam();
    void refreshAlACD();

signals:
    void refreshFormula();

};

#endif // CALCULATOR_PATIENT_H
