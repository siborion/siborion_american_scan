#ifndef SCANPLOT_H
#define SCANPLOT_H

#include <QWidget>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_slider.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qlayout.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <QFileDialog>
#include <QPushButton>

class ScanPlot : public QWidget
{
    Q_OBJECT
public:
    explicit ScanPlot(QWidget *parent = 0);

private:
    QGridLayout *layout;
    QwtPlot *q_plot;
    QwtPlotMarker mX;
//    QwtPlotCanvas *canvas;
//    QwtPlotCurve *d_curve1;
    QFileDialog *fileName;
    QPushButton *pbTmp;
    void getPlot(QwtPlot*);
    double x[10];
    double y[10];


signals:

public slots:

private slots:
    void changeVal(double);

};

#endif // SCANPLOT_H
