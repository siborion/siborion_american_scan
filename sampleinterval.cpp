#include "sampleinterval.h"
#include <qwt_plot.h>

SampleInterval::SampleInterval(double x1, double x2, QString title):
    QwtPlotCurve()
{
    double x[2];
    double y[2];

    x[0] = x1;
    x[1] = x2;
    y[0] = y[1] = -6;

    setXAxis(QwtPlot::xBottom);

    setPen( Qt::darkBlue, 10 );
    setTitle(title);
//    const QColor &c = Qt::darkBlue;
//    setSymbol(new QwtSymbol(QwtSymbol::NoSymbol, Qt::blue, c, QSize(24,24)));
    setSamples(x,y,2);
}
