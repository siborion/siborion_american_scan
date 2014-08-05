#ifndef CALCULATOR_PATIENT_H
#define CALCULATOR_PATIENT_H

#include <QWidget>

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
};

#endif // CALCULATOR_PATIENT_H
