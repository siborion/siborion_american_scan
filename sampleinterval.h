#ifndef SAMPLEINTERVAL_H
#define SAMPLEINTERVAL_H
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

class SampleInterval : public QwtPlotCurve
{
public:
    SampleInterval(double x1, double x2, QString title);
};

#endif // SAMPLEINTERVAL_H
