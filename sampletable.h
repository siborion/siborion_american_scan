#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include <QStandardItem>
#include <QPushButton>
//#include <QSound>
#include "plot.h"
#include "curparam.h"
#include "listresult.h"
#include "delegateprint.h"

class sampletable : public QFrame
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0, CurParam *link = 0);
    adjview *twMeas;
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*, bool fromBase = false);
    void editSample(quint16 rowNom, stMeasureParam* measureParam);

private:
    DelegatePrint *delegatePrint;
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
    void keyPressEvent(QKeyEvent * keyEvent);
//    QSound *bells;

signals:
    void changeRow(stMeasureParam*);
    void sendAvg(stAverageParam*);
    void stopMeasure();
    void save(QStandardItemModel *,QStandardItemModel *);
    void changeGlas();
    void clearAllSignal();
    void clearSample();

public slots:
    void changeRowSlot(QModelIndex curIndex);
    void editSample(stMeasureParam* measureParam);
    void changeRegimManual(QString);
    void startMeasure();
    void saveSlot();
    void loadSlot();
    void clearAll();
    void del();
    void changeGlasSlot();
    void slPrintChange(QModelIndex);
};

#endif // SAMPLETABLE_H
