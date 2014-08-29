#ifndef CALCULATOR_PATIENT_H
#define CALCULATOR_PATIENT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include "typedef.h"

namespace Ui {
class calculator_patient;
}

class calculator_patient : public QWidget
{
    Q_OBJECT

public:
    explicit calculator_patient(QWidget *parent = 0);
    ~calculator_patient();

private:
    Ui::calculator_patient *ui;
    stPatientParam patientParam;

public:
    void setPatient(quint16 id, QString Patient, QString Doctor);
    void refreshPatientParam();
//    double K, AL_measure, ACD_measure;
    bool bLeft;
    stPatientParam getParam();
    stPersonalParam getPersonalParam();
//    quint16 curId;
    void refreshMeasure(stMeasureParam measureParam);

private slots:
    void RefreshK();
    void ChangeSide();
    void updateParam();

signals:
    void refreshFormula();

};

#endif // CALCULATOR_PATIENT_H
