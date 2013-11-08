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

    insertCurve( Qt::Vertical, Qt::red, 5.0 );


    mX = new QwtPlotMarker();
    mX->setLabel( QString::fromLatin1( "x = 2 pi" ) );
    mX->setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
    mX->setLabelOrientation( Qt::Vertical );
    mX->setLineStyle( QwtPlotMarker::VLine );
    mX->setLinePen( Qt::red, 0, Qt::DashDotLine );
    mX->setXValue( 2.0 * M_PI );
    mX->setXValue( 1.0 * M_PI );
    mX->attach( this );

    setAutoReplot( true );
}



void Plot::insertCurve( int axis, double base )
{
    Qt::Orientation o;
    if ( axis == yLeft || axis == yRight )
        o = Qt::Horizontal;
    else
        o = Qt::Vertical;

    QRgb rgb = static_cast<QRgb>( rand() );
    insertCurve( o, QColor( rgb ), base );
    replot();
}

void Plot::insertCurve( Qt::Orientation o,
    const QColor &c, double base )
{
    QwtPlotCurve *curve = new QwtPlotCurve();

    curve->setPen( c );
    curve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse,
        Qt::gray, c, QSize( 8, 8 ) ) );

    double x[2];
    double y[sizeof( x ) / sizeof( x[0] )];

    for ( uint i = 0; i < sizeof( x ) / sizeof( x[0] ); i++ )
    {
        double v = 5.0 + i * 10.0;
        if ( o == Qt::Horizontal )
        {
            x[i] = v;
            y[i] = base;
        }
        else
        {
            x[i] = base;
            y[i] = v;
        }
    }

    curve->setSamples( x, y, sizeof( x ) / sizeof( x[0] ) );
//    curve->setSamples( 5.0, 5.0, 100.0) ;
    curve->attach( this );
}

void MoveMarker()
{

}




