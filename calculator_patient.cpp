#include "calculator_patient.h"
#include "ui_calculator_patient.h"

calculator_patient::calculator_patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator_patient)
{
    ui->setupUi(this);
}

calculator_patient::~calculator_patient()
{
    delete ui;
}
