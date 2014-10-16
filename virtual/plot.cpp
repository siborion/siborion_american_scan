#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_widget.h>
#include <qmath.h>
#include "plot.h"
#include <qevent.h>
#include <qwt_plot_textlabel.h>

Plot::Plot( QWidget *parent, bool print):
    QwtPlot( parent )
{
    setAutoReplot( false );
    setAutoDelete(true);

    QwtPlotCanvas *canvas = new QwtPlotCanvas();

    setCanvas( canvas );

    if(print)
        setCanvasBackground(Qt::white);
    else
        setCanvasBackground(QColor("Black"));

    // axes
    enableAxis( QwtPlot::xTop );
    double dMin, dMax;
    dMin=(-20.0); dMax=(1024.0);
    setAxisScale(QwtPlot::xTop, dMin, dMax);
    setAxisScale(QwtPlot::xBottom, (dMin/27), (dMax/27));
    setAxisScale(QwtPlot::yLeft, -4, 280.0);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::gray);
    this->axisWidget(QwtPlot::yLeft)->setPalette(palette);
    palette.setColor(QPalette::Text, Qt::gray);
    this->axisWidget(QwtPlot::xBottom)->setPalette(palette);

    // curves
    d_curve1 = new QwtPlotCurve();
    d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    if(print)
        d_curve1->setPen( Qt::black );
    else
        d_curve1->setPen(QColor(255,170,0,255));   //( Qt::yellow );
    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve1->setYAxis(QwtPlot::yLeft);
    d_curve1->setXAxis(QwtPlot::xTop);
    d_curve1->attach(this);


    changeContactSlot(true);

    setAutoReplot( true );
}


void Plot::drawSample(const double *x, const double *y, int count)
{
    foreach (QwtPlotItem *p, itemList())
    {
        if(p->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            removeItem(p);
        }
    }
    d_curve1->setSamples(x, y, count );
}

void Plot::drawMarker(quint16 pos, QString title)
{
    QFont qF;
    qF.setPixelSize(20);
    QwtText qT;
    qT.setFont(qF);
    qT.setText(title);
    QColor color;
    color.setRgb(0,0,0,0);
    qT.setBackgroundBrush(color);
    QwtPlotMarker *d_marker = new QwtPlotMarker();
    d_marker->setXAxis(QwtPlot::xTop);
    d_marker->setLineStyle( QwtPlotMarker::VLine );
    d_marker->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker->setXValue((double)pos);
    d_marker->setTitle(title);
    d_marker->setLabel(qT);
    d_marker->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    d_marker->attach( this );
}

void Plot::drawMarker(double x, double y, const QColor &color)
{
    QwtPlotMarker *d_marker = new QwtPlotMarker();
    d_marker->setXAxis(QwtPlot::xTop);
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
        default:
            break;
    }
    return QObject::eventFilter( object, event );
}

void Plot::select( const QPoint &pos )
{
    QwtPlotMarker *curve = NULL;
    QwtPlotCurve  *markCurve = NULL;
    double dist = 10e10;
    int index = -1;
    int yValue;
    const QwtPlotItemList& itmList = itemList();

    d_selectedCurve = NULL;
    d_selectedMarkCurve = NULL;

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
    if ( curve && (dist < 10)) // 10 pixels tolerance
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
                        romb_selectedCurve = c;
                        break;
                    }
                }
            }
        }
        return;
    }

    dist = 10e10;
    for ( QwtPlotItemIterator it = itmList.begin();it != itmList.end(); ++it )
    {
        if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotCurve)
        {
            QwtPlotCurve *c = static_cast<QwtPlotCurve *>( *it );
            if((c->title().text()=="Start_Interval")||(c->title().text()=="Lens_Interval")||(c->title().text()=="Retina_Interval"))
            {
                double d;
                int idx = c->closestPoint( pos, &d );
                if ((d < dist) && (d>0.01))
                {
                    markCurve = c;
                    index = idx;
                    dist = d;
                }
            }
        }
    }

    d_selectedMarkCurve = NULL;
    d_selectedPoint = -1;

    if ( markCurve && (dist < 10)) // 10 pixels tolerance
    {
        d_selectedMarkCurve = markCurve;
        d_selectedPoint = index;
    }
}

void Plot::move( const QPoint &pos )
{
    quint16 val, in=0, curDist, dist=0xffff;
    if ( d_selectedCurve )
    {
        {
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
                }
            }
        }
    }

    if ( d_selectedMarkCurve )
    {
        QVector<double> xData( d_selectedMarkCurve->dataSize() );
        QVector<double> yData( d_selectedMarkCurve->dataSize() );
        for ( int i = 0; i < static_cast<int>( d_selectedMarkCurve->dataSize() ); i++ )
        {
            const QPointF sample = d_selectedMarkCurve->sample( i );
            if ( i == d_selectedPoint )
            {
                xData[i] = this->invTransform(d_selectedMarkCurve->xAxis(), pos.x());
                yData[i] = sample.y();
            }
            else
            {
                xData[i] = sample.x();
                yData[i] = sample.y();
            }
        }
        d_selectedMarkCurve->setSamples( xData, yData );
    }
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

void Plot::changeCataractSlot(bool visible)
{
}

void Plot::changeContactSlot(bool contact)
{
}
