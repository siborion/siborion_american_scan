#ifndef CALCULATOR_PATIENT_H
#define CALCULATOR_PATIENT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlRecord>


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

public:
    void setPatient(quint16 id, QString Patient, QString Doctor);
    void refreshPatientParam(quint16 id);
    double K, AL_measure, ACD_measure;
    bool bLeft;
    quint16 curId;

private slots:
    void RefreshK();
    void ChangeSide();

};

#endif // CALCULATOR_PATIENT_H
