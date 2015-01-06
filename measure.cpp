#include "measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout     = new QGridLayout(this);
//    QVBoxLayout *layout     = new QVBoxLayout(this);
//    QHBoxLayout *layoutTop  = new QHBoxLayout();
//    layout->addLayout(layoutTop);

    pPlot = new Plot(this, false);
    pBigViewCur = new Bigviewnumcur();

    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this, false);
    glPlot->addWidget(pBigViewCur);
    glPlot->addWidget(pPlot,1,0);


    layout->addWidget(fmPlot,0,0);

}
