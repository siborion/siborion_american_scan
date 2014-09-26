#ifndef calculator_H
#define calculator_H

#include <QFrame>
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
#include "calculator_patient.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDateTime>
#include "plot.h"
#include "curentparam.h"
#include "typedef.h"


class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = 0);
    void refreshAl();
    void refreshAcd();

    
signals:

private:
    CurentParam *curentParam;
    Plot *pPlotPrint1;
    Plot *pPlotPrint2;
    Plot *pPlotPrint3;
    double ACD_measure;
    quint16 patientCurId;
    _formulae stFormula;
//    QSqlQueryModel  *modelMainLens;
    QAbstractItemModel  *modelMainLens;
//    void refreshPatientParam(quint16 id);
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
//    adjview *twcalculator;
//    QStandardItemModel *modelcalculator;
//    adjview *twHead1;
//    adjview *twHead2;
//    adjview *twHead3;
//    adjview *twcalculator1;
//    adjview *twcalculator2;
//    adjview *twcalculator3;
//    QStandardItemModel *modelcalculator1;
    QFrame *frCalculator;
//    QComboBox *cbFormula1;
//    QComboBox *cbFormula2;
//    QComboBox *cbFormula3;
//    adjview *twVs1;
//    adjview *twVs2;
//    adjview *twVs3;
    QPushButton *pbPrint;
//    QPushButton *pbPersCalc;
    formula *Formula1;
    formula *Formula2;
    formula *Formula3;
    calculator_patient *pCalcPatient;

    QString baseMapName[3] = {
        "Patient ID",
        "Patient Name",
        "Doctor Name"
        };
    QString baseMapK[5] = {
        "AL",
        "K1-Value",
        "K2-Value",
        "K-Value",
        "ACD"
        };
    QString baseMapA[4] = {
        "A Const",
        "ACD",
        "SF",
        "Rx"
        };

public:
    void refreshMeasure();

private slots:
//    void setAL(QModelIndex,QModelIndex);

public slots:
    void changeRow(quint8 id ,quint16 id1 ,QString sTmp1, QString sTmp2);
//    void changeEye();
    void refreshFormuls();
    void printPreview();
    void print( QPrinter* printer );
//    void refreshMeasure(stMeasureParam);

};

#endif // calculator_H
