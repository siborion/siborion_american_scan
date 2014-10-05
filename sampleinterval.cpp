#include "sampleinterval.h"
#include <qwt_plot.h>

SampleInterval::SampleInterval(quint16 x1, quint16 x2, QString title):
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
    setSamples(x,y,2);
}

void SampleInterval::setSample(quint16 x1, quint16 x2)
{
    double x[2];
    double y[2];
    x[0] = x1;
    x[1] = x2;
    y[0] = y[1] = -6;
    setSamples(x,y,2);
}
