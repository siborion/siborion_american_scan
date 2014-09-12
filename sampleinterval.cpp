#include "sampleinterval.h"

SampleInterval::SampleInterval(quint16 x1, quint16 x2, QString title):
    QwtPlotCurve()
{
    double x[2];
    double y[2];

    x[0] = x1;
    x[1] = x2;
    y[0] = y[1] = -6;

    setPen( Qt::blue, 10 );
    setTitle(title);
    const QColor &c = Qt::blue;
    setSymbol(new QwtSymbol(QwtSymbol::NoSymbol, Qt::blue, c, QSize(24,24)));
    setSamples(x,y,2);
}
