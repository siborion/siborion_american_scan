#ifndef SAMPLEINTERVAL_H
#define SAMPLEINTERVAL_H
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

class SampleInterval : public QwtPlotCurve
{
public:
    SampleInterval(quint16 x1, quint16 x2, QString title);
    void setSample(quint16 x1, quint16 x2);
};

#endif // SAMPLEINTERVAL_H
