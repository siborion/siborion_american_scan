#include "printplot.h"
#include "curparam.h"

PrintPlot::PrintPlot(QWidget *parent, CurParam *tmpParam, QByteArray *sample):Plot(parent, true, tmpParam)
{

    qDebug()<<"PrintPlot";
//    QByteArray sample;
//    pPlotPrint = new Plot(this, true, &curParam);
//    drawSample(sample);
    enableAxis(QwtPlot::xTop,false);
    enableAxis(QwtPlot::xBottom,true);
    enableAxis(QwtPlot::yLeft,true);
    replot();
}
