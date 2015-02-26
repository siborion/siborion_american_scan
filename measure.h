#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include "plot.h"
#include "bigviewnumcur.h"
#include "key_radio.h"
#include "sampletable.h"
#include "velosity.h"
#include "bigviewnum.h"
#include "curparam.h"


class Measure : public QWidget
{
    Q_OBJECT
public:
    explicit Measure(QWidget *parent = 0, CurParam *link=0);
    void resiveData(QByteArray*);
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*);
    Plot *pPlot;
    sampletable *pSampleTable;

private:
    Bigviewnumcur *pBigViewCur;
    key_radio *pKey;
    Velosity *velosity;
    bigviewnum *pBigView;
    CurParam *curParam;
    QTime curTime;

    QByteArray SampleManual;
    QList<quint16> extremumManual;
    stMeasureParam measureParamManual;

public slots:
    void doScanSlot(bool*);
    void refreshTableSlot(stMeasureParam *);
    void stopMeasureSlot();
    void updatePatient();
    void changeGlasSlot();
    void saveSlot(QStandardItemModel *,QStandardItemModel *);
    void clearAll();
    void changeSideCalculatorSlot();

Q_SIGNALS:
    void doScan(bool*);
    void refreshTable(stMeasureParam *);
    void stopMeasure();
    void changeGlas();
    void save(QStandardItemModel *,QStandardItemModel *);
};

#endif // MEASURE_H
