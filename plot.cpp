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



Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{
    setAutoReplot( false );
    setAutoDelete(true);

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    setCanvas( canvas );
//    setCanvasBackground( QColor( "MidnightBlue" ) );
    setCanvasBackground(QColor("DarkSlateGray"));

    // grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( this );

    // axes
    enableAxis( QwtPlot::xTop );
    setAxisMaxMajor( QwtPlot::xBottom, 6 );
    setAxisMaxMinor( QwtPlot::xBottom, 9 );
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
    setAutoReplot( true );
//    this->setMaximumSize(200,200);
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
    qT.setBackgroundBrush(QBrush("DarkSlateGray"));
    QwtPlotMarker *d_marker = new QwtPlotMarker();
    d_marker->setLineStyle( QwtPlotMarker::VLine );
    d_marker->setLinePen( Qt::red, 0, Qt::SolidLine );
    d_marker->setXValue((double)pos);
    d_marker->setTitle(title);
//    d_marker->set
    d_marker->setLabel(qT);
    d_marker->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
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
    quint16 val, in=0, curDist, dist=0xffff;
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
                            extremum.append((kolvo-i)+1);
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
