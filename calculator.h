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
#include "calc.h"
#include "calculator_patient.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDateTime>
#include "plot.h"
#include "curparam.h"
#include "typedef.h"
#include "printplot.h"
#include "calclens.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = 0, CurParam *link=0);
    adjview *twMeas;
    void refreshAl();
    void refreshAcd();
    CalcLens *calcLens;
    
signals:

private:
    double al1, al2, al3, al4, acd1, acd2, acd3, acd4;
    QImage iPlot1, iPlot2, iPlot3, iPlot4;
    CurParam *curParam;
    PrintPlot *pPlotPrint1;
    Plot *pPlotPrint2;
    Plot *pPlotPrint3;
    Plot *pPlotPrint4;
    double ACD_measure;
    quint16 patientCurId;
    _formulae stFormula;
    adjview *twName;
    QStandardItemModel *modelName;
    adjview *twLens;
    adjview *twK;
    QStandardItemModel *modelK;
    adjview *twA;
    QStandardItemModel *modelA;
    adjview *twRx;
    QStandardItemModel *modelRx;
    QPushButton *pbPrint;
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
    formula *Formula1;
    formula *Formula2;
    formula *Formula3;

private slots:
    void changeSideCalculatorSlot();
    void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
    void setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage);

public slots:
    void updatePatient();
    void refreshFormuls();
    void printPreview();
    void refreshLens(QSqlQueryModel *link);

signals:
    void changeSideCalculator();

};

#endif // calculator_H
