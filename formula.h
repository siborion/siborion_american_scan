#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include <QFormLayout>
#include <adjview.h>
#include "calc.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <math.h>
#include "typedef.h"
#include "delegate_lens.h"

class formula : public QFrame
{
    Q_OBJECT
private:
    double AL;
    double K;
    double AConst;
    double ACD;
    double SF;
    double A0;
    double A1;
    double A2;
    double ACD_measure;
    double Rx;
    QLabel *lLens;
    QLabel *leLens;
    adjview *twCalculator;
    adjview *twFormula;
    adjview *twEmm;
    QComboBox *cbFormula;
    QStringList getListFormula();
    QStandardItem *getItem(QString, Qt::AlignmentFlag);
    QStandardItem *getItem(double, Qt::AlignmentFlag);
    void calculateIOL(quint8 formula);
    stFormulaInfo stInfo;

public:
    void setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, QString A0, QString A1, QString A2,  double K, double AL, double ACD, double Rx);
    stFormulaInfo *getModel();
    void clear();

public:
    explicit formula(QWidget *parent = 0);
    void saveParam(_formulae *val);
    
public slots:
//    void setAL(QModelIndex,QModelIndex);
    
private slots:
    void refreshFormula(int);
    void changeFotmula(int);
};

#endif // FORMULA_H
