#include "measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout     = new QGridLayout(this);

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

    layout->addWidget(fmPlot      ,0,0,2,1);
    layout->addWidget(pKey        ,2,0,1,2);
    layout->addWidget(pSampleTable,0,1);
    layout->addWidget(velosity    ,1,1);

}
