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

    layout->addWidget(fmPlot,0,0);
}
