#include "measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout     = new QVBoxLayout(this);
    QHBoxLayout *layoutTop  = new QHBoxLayout();
//    QVBoxLayout *layoutLeft = new QVBoxLayout(this);

    layout->addLayout(layoutTop);
//    layoutTop->addLayout(layoutLeft);

    pPlot = new Plot(this, false);

    layoutTop->addWidget(pPlot);

}
