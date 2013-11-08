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
//    void MoveMarker();

private Q_SLOTS:


private:
    void showData( const double *frequency, const double *amplitude,
        const double *phase, int count );

    void insertCurve( int axis, double base );
    void insertCurve( Qt::Orientation, const QColor &, double base );

    QwtPlotMarker *mX;
};

#endif
