#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>

class QwtPlotCurve;
class QwtPlotMarker;


class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent );

public Q_SLOTS:

private:
    void showData( const double *frequency, const double *amplitude,
        const double *phase, int count );
};

#endif
