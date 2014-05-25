#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include <QFormLayout>
#include <adjview.h>
#include "calc.h"
#include <QComboBox>


class formula : public QWidget
{
    Q_OBJECT
private:
    double AL;
    double K;
    double AConst;
    double ACD;
    double SF;

    adjview *twHead;
    adjview *twCalculator;
    adjview *twFormula;
    adjview *twEmm;
    QComboBox *cbFormula;
    QStringList getListFormula();
    QStandardItem *getItem(QString, Qt::AlignmentFlag);

public:
    void setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, double K, double AL);

public:
    explicit formula(QWidget *parent = 0);
    void saveParam(_formulae *val);
    
signals:
    
private slots:
    void refreshFormula(void);
};

#endif // FORMULA_H
