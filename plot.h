#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>
//#include <QApplication>
#include "sampleinterval.h"
#include "curparam.h"
//#include "typedef.h"

class QwtPlotCurve;
class QwtPlotMarker;


//struct stResultParam
//{
//    double ACD;
//    double LT;
//    double Vit;
//    double AL;

//    double AvgAl;
//    double AvgAcd;
//    double AvgLt;
//    double AvgVit;

//    double devAl;
//    double devAcd;
//    double devLt;
//    double devVit;

//    quint8 countSample;
////    double SD;
//};


class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent, bool print, CurParam *link = 0);
    void drawSample(const double *frequency, const double *amplitude, int count);
    void drawMarker(quint16 pos, QString title);
    void drawMarker(double x, double y, const QColor &);
    void drawMarker(quint16 pos, QString title, bool visible);
    virtual bool eventFilter( QObject *, QEvent * );
    QList<quint16> allExtremum;
    void drawSample(QByteArray *Sample);
    Plot *pPlot;
    CurParam *curParam;
    void clearMarker();

public slots:
    void updateSample(stMeasureParam *);
    void updateSample(stMeasureParam *, bool print);
    void updateInterval();
    void clearSample();

private:
    void select( const QPoint &pos );
    void move( const QPoint &pos );
    stMeasureParam measureParam;
    QwtText *startIntervalText;

    QwtPlotCurve *d_curve1;
    SampleInterval *startInterval;
    SampleInterval *lensInterval;
    SampleInterval *retinaInterval;
    QwtPlotCurve *d_selectedMarkCurve;
    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;
    QwtPlotMarker *d_marker3;
    QwtPlotMarker *d_selectedCurve;
    QwtPlotMarker *romb_selectedCurve;
    int d_selectedPoint;

signals:
    void refreshTable(stMeasureParam *);

};

#endif
