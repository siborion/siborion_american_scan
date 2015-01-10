#include "sampleinterval.h"
#include <qwt_plot.h>

SampleInterval::SampleInterval(quint16 x1, quint16 x2, QString title, CurParam *link):
    QwtPlotCurve()
{
    double x[2];
    double y[2];

    curParam = link;

    x[0] = x1;
    x[1] = x2;
    y[0] = y[1] = -6;

    setXAxis(QwtPlot::xBottom);

    setPen( Qt::darkBlue, 10 );
    setTitle(title);
    setSamples(x,y,2);


    if(this->title().text()== "Start_Interval")
    {
        curParam->corneaX1 = qMin(x1, x2);
        curParam->corneaX2 = qMax(x1, x2);
    }
    if(this->title().text()== "Lens_Interval")
    {
        curParam->lensX1 = qMin(x1, x2);
        curParam->lensX2 = qMax(x1, x2);
    }
    if(this->title().text()== "Retina_Interval")
    {
        curParam->retinaX1 = qMin(x1, x2);
        curParam->retinaX2 = qMax(x1, x2);
    }
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
