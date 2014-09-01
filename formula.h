#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include <QFormLayout>
#include <adjview.h>
#include "calc.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>


class formula : public QWidget
{
    Q_OBJECT
private:
    double AL;
    double K;
    double AConst;
    double ACD;
    double SF;
    double ACD_measure;

//    adjview *twHead;
    QLabel *lLens;
    QLineEdit *leLens;
    adjview *twCalculator;
    adjview *twFormula;
    adjview *twEmm;
    QComboBox *cbFormula;
    QStringList getListFormula();
    QStandardItem *getItem(QString, Qt::AlignmentFlag);
    QStandardItem *getItem(double, Qt::AlignmentFlag);
    void calculateIOL(quint8 formula);

public:
    void setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, double K, double AL, double ACD);
    QStandardItemModel *getModel();

public:
    explicit formula(QWidget *parent = 0);
    void saveParam(_formulae *val);
    
public slots:
    void setAL(QModelIndex,QModelIndex);
    
private slots:
    void refreshFormula(int);
    void changeFotmula(int);
};

#endif // FORMULA_H
