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
#include <QApplication>

Plot::Plot( QWidget *parent, bool print, CurParam *link):
    QwtPlot( parent )
{
    setMinimumHeight(150);
    setMinimumWidth (150);

    curParam = link;

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
    setAxisScale(QwtPlot::yLeft, -4, 600.0);

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
        d_curve1->setPen(QColor(255,255,255,255));   //( Qt::yellow );
    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve1->setYAxis(QwtPlot::yLeft);
    d_curve1->setXAxis(QwtPlot::xTop);
    d_curve1->attach(this);

    if(!print)
    {
        startInterval  = new SampleInterval(0, 0, "Start_Interval", curParam);
        lensInterval   = new SampleInterval(0, 0, "Lens_Interval",  curParam);
        retinaInterval = new SampleInterval(0, 0, "Retina_Interval",curParam);
        startInterval->setXAxis(QwtPlot::xTop);
        lensInterval->setXAxis(QwtPlot::xTop);
        retinaInterval->setXAxis(QwtPlot::xTop);
        startInterval->attach( this );
        lensInterval->attach( this );
        retinaInterval->attach( this );
        updateInterval();
    }
    setAutoReplot( true );
}

void Plot::drawSample(QByteArray *Sample)
{
    QVector<double>  xData, yData;
    quint16 kolvo = 0;
    foreach(quint8 val, *Sample)
    {
        xData.append(kolvo);
        yData.append(val*2);
        kolvo++;
    }
    foreach (QwtPlotItem *p, itemList())
    {
        if(p->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            removeItem(p);
        }
    }
    d_curve1->setSamples(xData, yData);
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
    d_marker->setLinePen( Qt::blue, 0, Qt::SolidLine );
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
//    int yValue;
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
//    stMainParam mainParam;
    quint16 val, in=0, curDist, dist=0xffff;
    if ( d_selectedCurve )
    {
        if((d_selectedCurve->title().text()=="Cornea")||(d_selectedCurve->title().text()=="L1")||(d_selectedCurve->title().text()=="L2")||(d_selectedCurve->title().text()=="Retina"))
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
                    if(c->title().text()=="Cornea")
                        measureParam.Cornea = c->xValue();
                    if(c->title().text()=="L1")
                        measureParam.L1 = c->xValue();
                    if(c->title().text()=="L2")
                        measureParam.L2 = c->xValue();
                    if(c->title().text()=="Retina")
                        measureParam.Retina = c->xValue();
                    emit(refreshTable(&measureParam));
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
                if(xData[i]<0)
                    xData[i]=0;
                yData[i] = sample.y();
            }
            else
            {
                xData[i] = sample.x();
                yData[i] = sample.y();
            }
        }
        if(d_selectedMarkCurve->title().text()== "Start_Interval")
        {
            curParam->corneaX1 = qMin(xData[0], xData[1]);
            curParam->corneaX2 = qMax(xData[0], xData[1]);
        }
        if(d_selectedMarkCurve->title().text()== "Lens_Interval")
        {
            curParam->lensX1 = qMin(xData[0], xData[1]);
            curParam->lensX2 = qMax(xData[0], xData[1]);
        }
        if(d_selectedMarkCurve->title().text()== "Retina_Interval")
        {
            curParam->retinaX1 = qMin(xData[0], xData[1]);
            curParam->retinaX2 = qMax(xData[0], xData[1]);
        }
        d_selectedMarkCurve->setSamples( xData, yData );
    }
}


void Plot::updateSample(stMeasureParam *link)
{
    measureParam = *link;
    drawSample(&measureParam.Sample);
    drawMarker(measureParam.Cornea,"Cornea");
    drawMarker((double)measureParam.Cornea,(double)60, Qt::white);
    drawMarker(measureParam.L1,"L1");
    drawMarker((double)measureParam.L1,(double)60, Qt::white);
    drawMarker(measureParam.L2,"L2");
    drawMarker((double)measureParam.L2,(double)60, Qt::white);
    drawMarker(measureParam.Retina,"Retina");
    drawMarker((double)measureParam.Retina,(double)60, Qt::white);
    allExtremum = measureParam.extremum;
}

void Plot::updateInterval()
{
    double offSet;
    offSet=((curParam->regimContact==REGIM::CONTACT)?0:3.5*27);
    curParam->corneaX1 = 0+offSet;   curParam->corneaX2 = 22+offSet;
    curParam->lensX1 = 54+offSet;    curParam->lensX2 = 351+offSet;
    curParam->retinaX1 = 459+offSet; curParam->retinaX2 = 864+offSet;
    if((curParam->regimMeasure == REGIM::MANUAL)||(curParam->regimCataract == REGIM::APHAKIC))
    {curParam->lensX1 = 0;    curParam->lensX2 = 0;}

    startInterval->setSample (curParam->corneaX1, curParam->corneaX2);
    lensInterval->setSample  (curParam->lensX1,   curParam->lensX2);
    retinaInterval->setSample(curParam->retinaX1, curParam->retinaX2);
}

void Plot::clearAll()
{
    foreach (QwtPlotItem *p, itemList())
    {
        if(p->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            removeItem(p);
        }
    }
}

