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

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = 0);
    
signals:

private:
    adjview *twName;
    QStandardItemModel *modelName;
    adjview *twLens;
    QStandardItemModel *modelLens;
    adjview *twK;
    QStandardItemModel *modelK;
    adjview *twA;
    QStandardItemModel *modelA;
    adjview *twCalculator;
    QStandardItemModel *modelCalculator;
    adjview *twCalculator1;
    QStandardItemModel *modelCalculator1;

public slots:
    
};

#endif // CALCULATOR_H
