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
    QStandardItemModel *modelPatient;
    QStandardItemModel *modelLens;
    QStandardItemModel *modelVelocity;

signals:

public slots:

};

#endif // MESUREMENT_H
