#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>
#include <QApplication>

class QwtPlotCurve;
class QwtPlotMarker;

struct stMainParam
{
    quint16 Start;
    quint16 L1;
    quint16 L2;
    quint16 Retina;
};

struct stResultParam
{
    double ACD;
    double LT;
    double Vit;
    double AL;
};


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
    bool findMainParam(QList<quint16> *extremum, stMainParam &mainParam);
    bool findExtremum(QByteArray *Sample, QList<quint16> &extremum);
    QList <double> intToMM(QList<quint16> *mainParam);
    QList<quint16> allExtremum;

public Q_SLOTS:
//    void setDamp( double damping );

private:
//    void showData( const double *frequency, const double *amplitude,
//        const double *phase, int count );
//    void showPeak( double freq, double amplitude );
//    void show3dB( double freq );
    void select( const QPoint &pos );
    void move( const QPoint &pos );

    QwtPlotCurve *d_curve1;
    QwtPlotCurve *d_curve2;
    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;
    QwtPlotMarker *d_marker3;
//    QwtPlotMarker *d_marker4;
    QwtPlotMarker *d_selectedCurve;
    QwtPlotMarker *romb_selectedCurve;
    int d_selectedPoint;

Q_SIGNALS:
    void refreshTable(stMainParam mainParam);

};

#endif
