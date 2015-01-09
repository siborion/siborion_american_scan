#include "measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout     = new QGridLayout(this);

    layout->setVerticalSpacing(2);

    pBigViewCur = new Bigviewnumcur();
    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this, false);
    glPlot->addWidget(pBigViewCur, 0, 0);
    glPlot->addWidget(pPlot,       1, 0);

    pKey = new key_radio();
    pSampleTable = new sampletable();
    velosity = new Velosity();
    pBigView = new bigviewnum();

    layout->addWidget(fmPlot      ,0,0,3,1);
    layout->addWidget(pKey        ,3,0,1,2);
    layout->addWidget(pSampleTable,0,1);
    layout->addWidget(velosity    ,1,1);
    layout->addWidget(pBigView    ,2,1);

    connect(velosity,SIGNAL(doScan(bool*)),SLOT(doScanSlot(bool*)));
}

void Measure::doScanSlot(bool *doMeasure)
{
    emit doScan(doMeasure);
}

void Measure::resiveDataSlot(QByteArray Sample)
{
    pPlot->drawSample(Sample);
}

