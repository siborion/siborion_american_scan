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
    void drawSample(const double *frequency, const double *amplitude, int count);
    void drawMarker(quint8 nomMarker, quint16 pos);
    void drawMarker(double x, double y);

public Q_SLOTS:
    void setDamp( double damping );

private:
    void showData( const double *frequency, const double *amplitude,
        const double *phase, int count );
    void showPeak( double freq, double amplitude );
    void show3dB( double freq );

    QwtPlotCurve *d_curve1;
    QwtPlotCurve *d_curve2;
    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;
    QwtPlotMarker *d_marker3;
//    QwtPlotMarker *d_marker4;
};

#endif
