#include "printplot.h"
#include "curparam.h"

PrintPlot::PrintPlot()
{
    CurParam curParam;
    QByteArray sample;
    pPlotPrint = new Plot(this, true, &curParam);
    pPlotPrint->drawSample(&sample);
    pPlotPrint->enableAxis(QwtPlot::xTop,false);
    pPlotPrint->enableAxis(QwtPlot::xBottom,true);
    pPlotPrint->enableAxis(QwtPlot::yLeft,true);
    pPlotPrint->replot();
}
