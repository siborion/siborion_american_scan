#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_canvas.h>
#include <qmath.h>
//#include "complexnumber.h"
#include "plot.h"

#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif

Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{
    setAutoReplot( false );

    setTitle( "retina peak" );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setBorderRadius( 10 );

    setCanvas( canvas );
    setCanvasBackground( QColor( "MidnightBlue" ) );

    // legend
    QwtLegend *legend = new QwtLegend;
    insertLegend( legend, QwtPlot::BottomLegend );

    // grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( this );

    // axes
    enableAxis( QwtPlot::yRight );
    setAxisTitle( QwtPlot::xBottom, "Text1" );
    setAxisTitle( QwtPlot::yLeft, "lens anterior maximum" );
    setAxisTitle( QwtPlot::yRight, "lens posterior maximum" );

//    setAxisMaxMajor( QwtPlot::xBottom, 6 );
//    setAxisMaxMinor( QwtPlot::xBottom, 9 );
//    setAxisScaleEngine( QwtPlot::xBottom, new QwtLogScaleEngine );

    setAutoReplot( true );
}

