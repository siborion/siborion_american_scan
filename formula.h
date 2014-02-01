#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include <QFormLayout>
#include <adjview.h>
#include <mydelegate.h>
#include <QComboBox>


class formula : public QWidget
{
    Q_OBJECT
private:
    adjview *twHead;
    adjview *twCalculator;
    adjview *twFormula;
    adjview *twEmm;
    QComboBox *cbFormula;
    QStringList getListFormula();
    QStandardItem *getItem(QString, Qt::AlignmentFlag);

public:
    explicit formula(QWidget *parent = 0);
    
signals:
    
private slots:
    void refreshFormula(void);
};

#endif // FORMULA_H
