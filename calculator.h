#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QFormLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QGroupBox>
#include <QSpacerItem>
#include <QRadioButton>
#include <adjview.h>
#include <formula.h>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQueryModel>
#include "scanbase.h"
#include "calc.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = 0);
    
signals:

private:
    quint16 patientCurId;
    _formulae stFormula;
    void refreshTable(quint16 id);
    QSqlQueryModel  *modelMainLens;
    void refreshPatientParam(quint16 id);
    scanbase *pBase;
    adjview *twName;
    QStandardItemModel *modelName;
    adjview *twLens;
    QStandardItemModel *modelLens;
    adjview *twK;
    QStandardItemModel *modelK;
    adjview *twA;
    QStandardItemModel *modelA;
    adjview *twRx;
    QStandardItemModel *modelRx;
    adjview *twCalculator;
    QStandardItemModel *modelCalculator;
//    adjview *twHead1;
//    adjview *twHead2;
//    adjview *twHead3;
//    adjview *twCalculator1;
//    adjview *twCalculator2;
//    adjview *twCalculator3;
//    QStandardItemModel *modelCalculator1;
    QFrame *frCalculator;
//    QComboBox *cbFormula1;
//    QComboBox *cbFormula2;
//    QComboBox *cbFormula3;
//    adjview *twVs1;
//    adjview *twVs2;
//    adjview *twVs3;
    QPushButton *pbOD;
    QPushButton *pbPersCalc;
    formula *Formula1;
    formula *Formula2;
    formula *Formula3;

    QString baseMapName[3] = {
        "Patient ID",
        "Patient Name",
        "Doctor Name"
        };
    QString baseMapK[4] = {
        "AL",
        "K1-Value",
        "K2-Value",
        "K-Value"
        };
    QString baseMapA[4] = {
        "A Const",
        "ACD",
        "SF",
        "Rx"
        };

private slots:
    void setAL(QModelIndex,QModelIndex);

public slots:
    void changeRow(quint8 id ,quint16 id1 ,QString sTmp1, QString sTmp2);
    void changeEye();
    void refreshAl(double);

};

#endif // CALCULATOR_H
