#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include <QStandardItem>
#include <QPushButton>
#include "plot.h"
#include "curparam.h"
#include "listresult.h"

class sampletable : public QWidget
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0, CurParam *link = 0);
    adjview *twMeas;
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*, bool fromBase = false);
    void editSample(quint16 rowNom, stMeasureParam* measureParam);

private:
    double AL;
    QModelIndex tableIndex;
    void refreshResult(quint8 rowNom);
    QStandardItemModel *modelOD;
    QStandardItemModel *modelOS;
    void calculateAvg();
    CurParam *curParam;
    QPushButton *pbSave;
    QPushButton *pbLoad;
    QPushButton *pbClear;

signals:
    void changeRow(stMeasureParam*);
    void sendAvg(stAverageParam*);
    void stopMeasure();
    void save(QStandardItemModel *,QStandardItemModel *);
    void changeGlas();

public slots:
    void changeRowSlot(QModelIndex curIndex);
    void editSample(stMeasureParam* measureParam);
    void changeRegimManual();
    void startMeasure();
    void saveSlot();
    void loadSlot();
    void clearAll();


};

#endif // SAMPLETABLE_H
