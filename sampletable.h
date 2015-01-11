#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include <QStandardItem>
#include "plot.h"
#include "curparam.h"

class sampletable : public QWidget
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0, CurParam *link = 0 );
    adjview *twMeas;
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*);
    void editSample(quint16 rowNom, stMeasureParam* measureParam);

private:
    double AL;
    QModelIndex tableIndex;
    void refreshResult(quint8 rowNom);
    QStandardItemModel *modelOD;
    QStandardItemModel *modelOS;
    void calculateAvg();
    CurParam *curParam;

signals:
    void changeRow(stMeasureParam*);
    void sendAvg(stAverageParam*);
    void stopMeasure();

public slots:
    void changeRowSlot(QModelIndex curIndex);
    void editSample(stMeasureParam* measureParam);
    void changeRegimManual();
    void startMeasure();


};

#endif // SAMPLETABLE_H
