#include "scanplot.h"

ScanPlot::ScanPlot(QWidget *parent) :
    QWidget(parent)
{
        QGridLayout *layout = new QGridLayout( this );

        QwtPlot *q_plot = new QwtPlot();
        canvas.setBorderRadius( 10 );
        q_plot->setCanvas(&canvas);
        q_plot->setCanvasBackground( QColor( "MidnightBlue" ) );

        QwtLegend *legend = new QwtLegend;
        q_plot->insertLegend( legend, QwtPlot::BottomLegend );

        QwtPlotGrid *grid = new QwtPlotGrid;
        grid->enableXMin( true );
        grid->setMajorPen( Qt::white, 0, Qt::DotLine );
        grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
        grid->attach( q_plot );

        q_plot->enableAxis( QwtPlot::yRight );
        q_plot->setAxisTitle( QwtPlot::xBottom, "Text1" );
        q_plot->setAxisTitle( QwtPlot::yLeft, "Text2" );
        q_plot->setAxisTitle( QwtPlot::yRight, "Text3" );

        mX.setLabel( QString::fromLatin1( "axis" ) );
        mX.setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
        mX.setLabelOrientation( Qt::Vertical );
        mX.setLineStyle( QwtPlotMarker::VLine );
        mX.setLinePen( Qt::red, 0, Qt::DashDotLine );
        mX.setXValue( 0.0);
        mX.attach( q_plot );

    d_curve1 = new QwtPlotCurve( "Amplitude" );
    d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    d_curve1->setPen( Qt::yellow );
    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve1->setYAxis( QwtPlot::yLeft );
    d_curve1->attach( q_plot );


        QwtSlider *slider = new QwtSlider();
        slider->setOrientation( Qt::Horizontal );
        slider->setScale( 0.0, 1000.0 );
        slider->setTotalSteps( 1000 );
        slider->setSingleSteps( 1 );

        q_plot->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
        layout->addWidget( q_plot, 0, 0 );
        layout->addWidget( slider );

        connect( slider, SIGNAL( valueChanged( double ) ), SLOT( changeVal( double ) ) );
}

void ScanPlot::changeVal(double Val)
{
      mX.setXValue( Val);
      canvas.replot();
}
