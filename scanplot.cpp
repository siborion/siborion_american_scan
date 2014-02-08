#include "scanplot.h"

ScanPlot::ScanPlot(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *pbTmp = new QPushButton("Test");
    QGridLayout *layout = new QGridLayout( this );
    QwtPlot *q_plot = new QwtPlot();
    ttt = q_plot;
    //    q_plot->setCanvasBackground( QColor( "MidnightBlue" ) );
    q_plot->setCanvasBackground( QColor( "Black" ) );
    q_plot->setAxisScale(QwtPlot::xBottom, 0.0, 1024.0);
    q_plot->setAxisScale(QwtPlot::yLeft, 0.0, 255.0);
    //    QwtLegend *legend = new QwtLegend;
    //    q_plot->insertLegend( legend, QwtPlot::BottomLegend );
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableXMin( true );
    grid->setMajorPen( Qt::darkGray, 0, Qt::SolidLine );
    grid->setMinorPen( Qt::darkGray, 0 , Qt::DashLine );
    //grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( q_plot );
//    getPlot(q_plot);
    layout->addWidget( q_plot, 0, 0 , 1 ,1);
    layout->addWidget(pbTmp, 1, 0);
    connect(pbTmp, SIGNAL(clicked()), this, SLOT(getTest()));
}

void ScanPlot::getTest()
{
    double x[4096];
    double y[4096];

    double Tmp;
    quint16 kolVo=0;
    QString fileName = QFileDialog::getOpenFileName();

    ttt->detachItems(QwtPlotItem::Rtti_PlotCurve);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    file.read(144);

    while (!file.atEnd())
    {
        x[kolVo] = kolVo;
        bool bOk;
        Tmp = file.read(1).toHex().toUInt(&bOk, 16);
        file.read(1);
        y[kolVo] = Tmp;

        kolVo++;
    }

    QwtPlotCurve *d_curve2 = new QwtPlotCurve();
    d_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
    d_curve2->setPen( Qt::yellow );
    //        d_curve2->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve2->setYAxis( QwtPlot::yLeft );
    d_curve2->setSamples((const double*)x, (const double*)y, 1024);
    d_curve2->attach( ttt );
    ttt->replot();
    file.close();
}
