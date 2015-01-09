#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>
//#include <QApplication>
#include "sampleinterval.h"
//#include "curentparam.h"
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
    Plot( QWidget *parent, bool print );
    void drawSample(const double *frequency, const double *amplitude, int count);
    void drawMarker(quint16 pos, QString title);
    void drawMarker(double x, double y, const QColor &);
    virtual bool eventFilter( QObject *, QEvent * );
    QList <double> intToMM(QList<quint16> *mainParam);
    QList<quint16> allExtremum;
    void drawSample(QByteArray Sample);

public slots:
    void changeKeySlot();

private:
    void select( const QPoint &pos );
    void move( const QPoint &pos );

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

Q_SIGNALS:

};

#endif
