#include "scanplot.h"

ScanPlot::ScanPlot(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *pbTmp = new QPushButton("Test");
    QGridLayout *layout = new QGridLayout( this );
    QwtPlot *q_plot = new QwtPlot();
    ttt = q_plot;
    q_plot->setCanvasBackground( QColor( "MidnightBlue" ) );
    QwtLegend *legend = new QwtLegend;
    q_plot->insertLegend( legend, QwtPlot::BottomLegend );
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( q_plot );
//    getPlot(q_plot);
    layout->addWidget( q_plot, 0, 0 , 1 ,1);
    layout->addWidget(pbTmp, 1, 0);
    connect(pbTmp, SIGNAL(clicked()), this, SLOT(getTest()));
}

void ScanPlot::getPlot(QwtPlot *plot)
{
//    x[0]=10; x[1]=20; x[2]=20; x[3]=30; x[4]=40; x[5]=40; x[6]=40; x[7]=40; x[8]=40; x[9]=40;
//    y[0]=0 ; y[1]=1; y[2]=2;  y[3]=3;  y[4]=4;  y[5]=5;  y[6]=6;  y[7]=7;  y[8]=8;  y[9]=9;
//    QwtPlotCurve *d_curve1 = new QwtPlotCurve();
//    d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
//    d_curve1->setPen( Qt::red );
//    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
//    d_curve1->setYAxis( QwtPlot::yLeft );
//    d_curve1->setSamples(y, x, 10);
//    d_curve1->attach( ttt );
}


void ScanPlot::getTest()
{
    quint8 x[4096];
    quint8 y[4096];
//    double x[4096];
//    double y[4096];

    quint8 Tmp;
    quint16 kolVo=0;
    QByteArray data;
    QString fileName = QFileDialog::getOpenFileName();
    qDebug() << fileName;

    ttt->detachItems(QwtPlotItem::Rtti_PlotCurve);

    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

//       file.read(144);

        while (!file.atEnd())
        {
            x[kolVo] = kolVo;
            file.read(1);
            Tmp = file.read(1).toUShort();
//            file.read(1);
            y[kolVo] = Tmp;
//            if(Tmp>100)
            qDebug() << Tmp;
//            qDebug() << "-";
//            qDebug() << y[kolVo];
//            qDebug() << "|";
            kolVo++;
        }


        QwtPlotCurve *d_curve2 = new QwtPlotCurve();
        d_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
        d_curve2->setPen( Qt::red );
        d_curve2->setLegendAttribute( QwtPlotCurve::LegendShowLine );
        d_curve2->setYAxis( QwtPlot::yLeft );
        d_curve2->setSamples((double const*)x, (double const*)y, 1000);
        d_curve2->attach( ttt );

        ttt->replot();

}
