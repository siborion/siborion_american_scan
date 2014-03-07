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
#include "complexnumber.h"
#include "plot.h"
#include <qevent.h>


#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif

//static void logSpace( double *array, int size, double xmin, double xmax )
//{
//    if ( ( xmin <= 0.0 ) || ( xmax <= 0.0 ) || ( size <= 0 ) )
//        return;

//    const int imax = size - 1;

//    array[0] = xmin;
//    array[imax] = xmax;

//    const double lxmin = log( xmin );
//    const double lxmax = log( xmax );
//    const double lstep = ( lxmax - lxmin ) / double( imax );

//    for ( int i = 1; i < imax; i++ )
//        array[i] = qExp( lxmin + double( i ) * lstep );
//}

Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{
    setAutoReplot( false );
    setAutoDelete(true);

//    setTitle( "Frequency Response of a Second-Order System" );

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
    enableAxis( QwtPlot::xTop );
//    setAxisTitle( QwtPlot::xBottom, "Normalized Frequency" );
//    setAxisTitle( QwtPlot::yLeft, "Amplitude [dB]" );
//    setAxisTitle( QwtPlot::yRight, "Phase [deg]" );

    setAxisMaxMajor( QwtPlot::xBottom, 6 );
    setAxisMaxMinor( QwtPlot::xBottom, 9 );
//    setAxisScaleEngine( QwtPlot::xBottom, new QwtLogScaleEngine );
    double dMin, dMax;
    dMin=(-20.0); dMax=(1024.0);
    setAxisScale(QwtPlot::xBottom, dMin, dMax);
    setAxisScale(QwtPlot::xTop, (dMin/27), (dMax/27));
    setAxisScale(QwtPlot::yLeft, 0.0, 255.0);


    // curves
    d_curve1 = new QwtPlotCurve();
    d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    d_curve1->setPen( Qt::yellow );
    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve1->setYAxis( QwtPlot::yLeft );
    d_curve1->attach( this );

    d_curve2 = new QwtPlotCurve();
    d_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
    d_curve2->setPen( Qt::cyan );
    d_curve2->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve2->setYAxis( QwtPlot::yRight );
    d_curve2->attach( this );

    // marker
    QwtText *L1 = new QwtText("L1");
    d_marker1 = new QwtPlotMarker();
    d_marker1->setVisible(false);
    d_marker1->setXValue( 0.0 );
    d_marker1->setLabel(*L1);
    d_marker1->setLineStyle( QwtPlotMarker::VLine );
    d_marker1->setLabelAlignment( Qt::AlignLeft | Qt::AlignTop );
    d_marker1->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker1->attach( this );


    QwtText *L2 = new QwtText("\r\nL2");
    d_marker2 = new QwtPlotMarker();
    d_marker2->setVisible(false);
    d_marker2->setXValue( 0.0 );
    d_marker2->setLabel(*L2);
    d_marker2->setLineStyle( QwtPlotMarker::VLine );
    d_marker2->setLabelAlignment( Qt::AlignLeft | Qt::AlignTop );
    d_marker2->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker2->attach( this );


    QwtText *Retina = new QwtText("\r\n\r\nRetina");
    d_marker3 = new QwtPlotMarker();
    d_marker3->setVisible(false);
    d_marker3->setXValue( 0.0 );
    d_marker3->setLabel(*Retina);
    d_marker3->setLineStyle( QwtPlotMarker::VLine );
    d_marker3->setLabelAlignment( Qt::AlignLeft | Qt::AlignTop );
    d_marker3->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker3->attach( this );

//    setDamp( 0.0 );
    setAutoReplot( true );

}

void Plot::showData( const double *frequency, const double *amplitude,
    const double *phase, int count )
{
    d_curve1->setSamples( frequency, amplitude, count );
    d_curve2->setSamples( frequency, phase, count );
}

void Plot::showPeak( double freq, double amplitude )
{
    QString label;
    label.sprintf( "Peak: %.3g dB", amplitude );

    QwtText text( label );
    text.setFont( QFont( "Helvetica", 10, QFont::Bold ) );
    text.setColor( QColor( 200, 150, 0 ) );

    d_marker2->setValue( freq, amplitude );
    d_marker2->setLabel( text );
}

void Plot::show3dB( double freq )
{
    QString label;
    label.sprintf( "-3 dB at f = %.3g", freq );

    QwtText text( label );
    text.setFont( QFont( "Helvetica", 10, QFont::Bold ) );
    text.setColor( Qt::green );

    d_marker1->setValue( freq, 0.0 );
    d_marker1->setLabel( text );
}

//
// re-calculate frequency response
//
//void Plot::setDamp( double damping )
//{
//    const bool doReplot = autoReplot();
//    setAutoReplot( false );

//    const int ArraySize = 200;

//    double frequency[ArraySize];
//    double amplitude[ArraySize];
//    double phase[ArraySize];

//    // build frequency vector with logarithmic division
//    logSpace( frequency, ArraySize, 0.01, 100 );

//    int i3 = 1;
//    double fmax = 1;
//    double amax = -1000.0;

//    for ( int i = 0; i < ArraySize; i++ )
//    {
//        double f = frequency[i];
//        const ComplexNumber g =
//            ComplexNumber( 1.0 ) / ComplexNumber( 1.0 - f * f, 2.0 * damping * f );

//        amplitude[i] = 20.0 * log10( qSqrt( g.real() * g.real() + g.imag() * g.imag() ) );
//        phase[i] = qAtan2( g.imag(), g.real() ) * ( 180.0 / M_PI );

//        if ( ( i3 <= 1 ) && ( amplitude[i] < -3.0 ) )
//            i3 = i;
//        if ( amplitude[i] > amax )
//        {
//            amax = amplitude[i];
//            fmax = frequency[i];
//        }

//    }
//    double f3 = frequency[i3] - ( frequency[i3] - frequency[i3 - 1] )
//        / ( amplitude[i3] - amplitude[i3 -1] ) * ( amplitude[i3] + 3 );
//    setAutoReplot( doReplot );
//    replot();
//}

void Plot::drawSample(const double *x, const double *y, int count)
{
    QwtPlotMarker *d;
    foreach (QwtPlotItem *p, itemList())
    {
        d = (QwtPlotMarker*)p;
//        p->setXAxis();
        if(p->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
//                    d = (QwtPlotMarker*)p;
//                    d->setXValue(d->xValue()+10);
            removeItem(p);
        }
    }
    d_curve1->setSamples(x, y, count );
}

void Plot::drawMarker(quint16 pos, QString title)
{
    QwtPlotMarker *d_marker = new QwtPlotMarker();
    d_marker->setLineStyle( QwtPlotMarker::VLine );
    d_marker->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker->setXValue((double)pos);
    d_marker->setTitle(title);
    d_marker->setLabel(title);
    d_marker->setLabelAlignment( Qt::AlignLeft | Qt::AlignTop );
    d_marker->attach( this );
}

void Plot::drawMarker(double x, double y, const QColor &color)
{
    QwtPlotMarker *d_marker = new QwtPlotMarker();
    d_marker->setLineStyle( QwtPlotMarker::NoLine );
    d_marker->setLinePen( color, 0, Qt::SolidLine );
    d_marker->setSymbol( new QwtSymbol( QwtSymbol::Diamond,QColor( color ), QColor( color ), QSize( 8, 8 ) ) );
    d_marker->setValue(x, y);
    d_marker->attach( this );
}


bool Plot::eventFilter( QObject *object, QEvent *event )
{

    switch( event->type() )
    {
        case QEvent::FocusIn:
        {
//            showCursor( true );
            break;
        }
        case QEvent::FocusOut:
        {
//            showCursor( false );
            break;
        }
        case QEvent::Paint:
        {
//            QApplication::postEvent( this, new QEvent( QEvent::User ) );
            break;
        }
        case QEvent::MouseButtonPress:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );
            select( mouseEvent->pos() );
            return true;
        }
        case QEvent::MouseMove:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent *>( event );
            move( mouseEvent->pos() );
            return true;
        }
        case QEvent::KeyPress:
        {
            const QKeyEvent *keyEvent = static_cast<QKeyEvent *>( event );

            const int delta = 5;
            switch( keyEvent->key() )
            {
                case Qt::Key_Up:
                {
//                    shiftCurveCursor( true );
                    return true;
                }
                case Qt::Key_Down:
                {
//                    shiftCurveCursor( false );
                    return true;
                }
                case Qt::Key_Right:
                case Qt::Key_Plus:
                {
//                    if ( d_selectedCurve )
//                        shiftPointCursor( true );
//                    else
//                        shiftCurveCursor( true );
                    return true;
                }
                case Qt::Key_Left:
                case Qt::Key_Minus:
                {
//                    if ( d_selectedCurve )
//                        shiftPointCursor( false );
//                    else
//                        shiftCurveCursor( true );
                    return true;
                }


                case Qt::Key_1:
                {
//                    moveBy( -delta, delta );
                    break;
                }
                case Qt::Key_2:
                {
//                    moveBy( 0, delta );
                    break;
                }
                case Qt::Key_3:
                {
//                    moveBy( delta, delta );
                    break;
                }
                case Qt::Key_4:
                {
//                    moveBy( -delta, 0 );
                    break;
                }
                case Qt::Key_6:
                {
//                    moveBy( delta, 0 );
                    break;
                }
                case Qt::Key_7:
                {
//                    moveBy( -delta, -delta );
                    break;
                }
                case Qt::Key_8:
                {
//                    moveBy( 0, -delta );
                    break;
                }
                case Qt::Key_9:
                {
//                    moveBy( delta, -delta );
                    break;
                }
                default:
                    break;
            }
        }
        default:
            break;
    }

    return QObject::eventFilter( object, event );
}

void Plot::select( const QPoint &pos )
{
    QwtPlotMarker *curve = NULL;
    double dist = 10e10;
    int index = -1;
    const QwtPlotItemList& itmList = itemList();
    for ( QwtPlotItemIterator it = itmList.begin();it != itmList.end(); ++it )
    {
        if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            QwtPlotMarker *c = static_cast<QwtPlotMarker *>( *it );
            if((c->title().text()=="Start")||(c->title().text()=="L1")||(c->title().text()=="L2")||(c->title().text()=="Retina"))
            {
                double d;
                d = abs(c->xValue() - (invTransform(c->xAxis(), pos.x())));
                int idx = c->xValue();
                if ( d < dist )
                {
                    curve = c;
                    index = idx;
                    dist = d;
                }
            }
        }
    }
    if ( curve && dist < 10 ) // 10 pixels tolerance
    {
        d_selectedCurve = curve;
        d_selectedPoint = index;
        for ( QwtPlotItemIterator it = itmList.begin();it != itmList.end(); ++it )
        {
            if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotMarker)
            {
                QwtPlotMarker *c = static_cast<QwtPlotMarker *>( *it );
                if((c->title().text()!="Start")&&(c->title().text()!="L1")&&(c->title().text()!="L2")&&(c->title().text()!="Retina"))
                {
                    if (d_selectedPoint == c->xValue())
                    {
//                        curve = c;
                        romb_selectedCurve = c;
                        break;
                    }
                }
            }
        }
    }
}

void Plot::move( const QPoint &pos )
{
    stMainParam mainParam;
    quint16 val, in, curDist, dist=0xffff;
    if ( !d_selectedCurve )
        return;

    if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == false)
    {
        foreach(val, allExtremum)
        {
            curDist = abs(val-(invTransform(d_selectedCurve->xAxis(), pos.x())));
            if(dist>curDist)
            {
                in = val;
                dist = curDist;
            }
        }
        d_selectedCurve->setXValue(in);
        romb_selectedCurve->setXValue(in);
    }
    else
        d_selectedCurve->setXValue(invTransform(d_selectedCurve->xAxis(), pos.x()));

    const QwtPlotItemList& itmList = itemList();
    for ( QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it )
    {
        if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            QwtPlotMarker *c = static_cast<QwtPlotMarker *>( *it );

            if(c->title().text()=="Start")
                mainParam.Start = c->xValue();
            if(c->title().text()=="L1")
                mainParam.L1 = c->xValue();
            if(c->title().text()=="L2")
                mainParam.L2 = c->xValue();
            if(c->title().text()=="Retina")
                mainParam.Retina = c->xValue();
        }
    }
    emit(refreshTable(mainParam));
}



bool Plot::findExtremum(QByteArray *Sample, QList<quint16> &extremum)
{
#define sampleStart 5
#define sampleEnd   1024
#define pik         (255*0.9)
#define spad        (60)
    quint16 kolvo = 0;
    bool front = true;
    foreach (quint8 val, *Sample)
    {
        if(kolvo>sampleStart)
        {
            if(val>pik)
            {
                if (front)
                {
                    for(int i=1; i<=5; i++)
                    {
                        if(((quint8)(Sample->at(kolvo-i)))<spad)
                        {
//                            pPlot->drawMarker(double((kolvo-i)+1), double(quint8(Sample->at((kolvo-i)+1))));
                            extremum.append((kolvo-i)+1);
//                            qDebug()<<(quint8)(Sample->at((kolvo-i)+1));
                            break;
                        }
                    }
                }
                front = false;
            }
            else
            {
                if(val<spad)
                    front = true;
            }
        }
        kolvo++;
        if(kolvo>sampleEnd)
            break;
    }

    allExtremum = extremum;

    return (extremum.count()>=3?true:false) ;
}

bool Plot::findMainParam(QList<quint16> *extremum, stMainParam &mainParam)
{
    quint16 Start, L1, L2, Retina, val;
    Start=L1=L2=Retina=0;

    for(int i=0; i<extremum->count();i++)
    {
        val = extremum->at(i);
        if(Start==0)
            Start = val;
        if((L1==0)&&(val>(Start+54))&&(val<(Start+162)))
            L1 = val;
        if((L2==0)&&(val>(L1+54))&&(val<(L1+162)))
            L2 = val;
        if((Retina==0)&&(val>(Start+459)))
            Retina = val;

    }
    if((Start>0)&&(L1>0)&&(L2>0)&&(Retina>0))
    {
        mainParam.Start = Start;
        mainParam.L1 = L1;
        mainParam.L2 = L2;
        mainParam.Retina = Retina;
        return true;
    }
    else
        return false;
}

QList <double> Plot::intToMM(QList<quint16> *mainParam)
{
    QList <double> ret;
    ret.clear();
    ret.append((double)(round(mainParam->at(0)*100/27)/100));
    ret.append((double)(round(mainParam->at(1)*100/27)/100));
    ret.append((double)(round(mainParam->at(2)*100/27)/100));
    ret.append((double)(round(mainParam->at(3)*100/27)/100));
    return ret;
}









