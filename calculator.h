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
#include <mydelegate.h>

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


public slots:
    
};

#endif // CALCULATOR_H
