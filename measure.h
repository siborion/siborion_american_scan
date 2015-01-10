#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "plot.h"
#include "bigviewnumcur.h"
#include "key_radio.h"
#include "sampletable.h"
#include "velosity.h"
#include "bigviewnum.h"


class Measure : public QWidget
{
    Q_OBJECT
public:
    explicit Measure(QWidget *parent = 0);
    void resiveData(QByteArray*);
    void addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*);
    Plot *pPlot;

private:
    Bigviewnumcur *pBigViewCur;
    key_radio *pKey;
    sampletable *pSampleTable;
    Velosity *velosity;
    bigviewnum *pBigView;

public slots:
    void doScanSlot(bool*);

Q_SIGNALS:
    void doScan(bool*);
};

#endif // MEASURE_H
