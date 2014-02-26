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
    void drawMarker(quint16 pos, QString title);
    void drawMarker(double x, double y, const QColor &);
    virtual bool eventFilter( QObject *, QEvent * );
//    virtual bool event( QEvent * );
    bool findMainParam(QList<quint16> *extremum, QList<quint16> &mainParam);
    bool findExtremum(QByteArray *Sample, QList<quint16> &extremum);
    QList <double> intToMM(QList<quint16> *mainParam);

public Q_SLOTS:
    void setDamp( double damping );

private:
    void showData( const double *frequency, const double *amplitude,
        const double *phase, int count );
    void showPeak( double freq, double amplitude );
    void show3dB( double freq );
    void select( const QPoint &pos );
    void move( const QPoint &pos );

    QwtPlotCurve *d_curve1;
    QwtPlotCurve *d_curve2;
    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;
    QwtPlotMarker *d_marker3;
//    QwtPlotMarker *d_marker4;
    QwtPlotMarker *d_selectedCurve;
    int d_selectedPoint;

};

#endif
