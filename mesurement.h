#ifndef MESUREMENT_H
#define MESUREMENT_H

#include <QWidget>
#include <qlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QStandardItemModel>
#include "scanplot.h"
#include <adjview.h>


class mesurement : public QWidget
{
    Q_OBJECT
public:
    explicit mesurement(QWidget *parent = 0);

private:
    adjview *twPatient;
    adjview *twLens;
    adjview *twVelocity;
    adjview *twMeas;
    QStandardItemModel *modelPatient;
    QStandardItemModel *modelLens;
    QStandardItemModel *modelVelocity;
    QStandardItemModel *modelMeas;

    QString baseMapPatient[4] = {
        "Patient ID",
        "Patient Name",
        "Date", 
        "Doctor Name"
        };

    QString baseMapLens[4] = {
        "Axial Length As: ACD+LT+VIT",
        "ACD @ 1532 m/sec",
        "LT @ 1641 m/sec",
        "VIT @ 1532 m/sec"
        };

    QString baseMapVelocity[3] = {
        "AL @ Ave. Velocity 1550 m/sec",
        "Average",
        "SD"
        };

signals:

public slots:

};

#endif // MESUREMENT_H
