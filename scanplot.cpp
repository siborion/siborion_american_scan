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
        q_plot->setAxisTitle( QwtPlot::yLeft, "lens anterior maximum" );
        q_plot->setAxisTitle( QwtPlot::yRight, "lens posterior maximum" );

        mX.setLabel( QString::fromLatin1( "x = 2 pi" ) );
        mX.setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
        mX.setLabelOrientation( Qt::Vertical );
        mX.setLineStyle( QwtPlotMarker::VLine );
        mX.setLinePen( Qt::red, 0, Qt::DashDotLine );
        mX.setXValue( 222.0);
        mX.attach( q_plot );
        mX.setXValue( 333.0);

        QwtSlider *slider = new QwtSlider();
        slider->setOrientation( Qt::Horizontal );
        slider->setScale( 0.0, 500.0 );
        slider->setTotalSteps( 500 );
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
