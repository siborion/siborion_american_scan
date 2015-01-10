#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include <QStandardItem>
#include "plot.h"

class sampletable : public QWidget
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0);
    adjview *twMeas;
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*);

private:
    double AL;
    QModelIndex tableIndex;
    void refreshResult(quint8 rowNom);
    QStandardItemModel *modelOD;
    QStandardItemModel *modelOS;

signals:
    void changeRow(stMeasureParam*);

public slots:
    void changeRowSlot(QModelIndex curIndex);
};

#endif // SAMPLETABLE_H
