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
//    QStandardItemModel *modelCalculator1;
//    QFrame *frCalculator;
    QComboBox *cbFormula;
//    adjview *twVs;

public:
    explicit formula(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // FORMULA_H
