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

private:
    Plot *pPlot;
    Bigviewnumcur *pBigViewCur;
    key_radio *pKey;
    sampletable *pSampleTable;
    Velosity *velosity;
    bigviewnum *pBigView;

public slots:
    void doScanSlot(bool*);
    void resiveDataSlot(QByteArray);

Q_SIGNALS:
    void doScan(bool*);
    void resiveData(QByteArray);

};

#endif // MEASURE_H
