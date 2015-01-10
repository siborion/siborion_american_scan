#ifndef SAMPLEINTERVAL_H
#define SAMPLEINTERVAL_H
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <curparam.h>

class SampleInterval : public QwtPlotCurve
{
public:
    SampleInterval(quint16 x1, quint16 x2, QString title, CurParam *link=0);
    void setSample(quint16 x1, quint16 x2);
    CurParam *curParam;
};

#endif // SAMPLEINTERVAL_H
