#include "panel.h"
#include "plot.h"
#include "knob.h"
#include "scanplot.h"

#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qwt_plot_curve.h>
#include <qwt_slider.h>
#include <qwt_symbol.h>


Panel::Panel( QWidget *parent ):
    QTabWidget( parent )
{
    setTabPosition( QTabWidget::North );
    addTab( createOnlineTab( this ), "Online" );
    addTab( createBaseTab( this ), "Base" );
    addTab( createBaseTab( this ), "Base1" );
}

QWidget *Panel::createOnlineTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );

//    d_amplitudeKnob = new Knob( "Amplitude", 0.0, 200.0, this );
//    d_amplitudeKnob->setValue( 160.0 );

    QGridLayout *layout = new QGridLayout( page );
//    layout->addWidget( new Plot( page), 0, 0 );

    ScanPlot *p_scan = new ScanPlot();

//    graf p_graf = new graf(this);

      layout->addWidget( p_scan, 0, 0 );

//    layout->addWidget( new graf( page), 0, 0 );
//    layout->addWidget(p_graf, 0, 0 );

//    layout->addWidget( d_amplitudeKnob, 0, 0 );

//    p_graf->setVal( 110.0 );


    changeVal1(510.0);

//    d_plot = new Plot( this );


    QwtSlider *slider = new QwtSlider();
    slider->setOrientation( Qt::Horizontal );
    slider->setScale( 0.0, 500.0 );
    slider->setTotalSteps( 500 );
    slider->setSingleSteps( 1 );
    layout->addWidget( slider );

//    connect( slider, SIGNAL( valueChanged( double ) ), SLOT( changeVal( double ) ) );


    return page;
}

QWidget *Panel::createBaseTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    return page;
}


void Panel::changeVal(double Val)
{
//if(p_graf)
//    p_graf->setVal( 310.0 );
}

void Panel::changeVal1(double Val)
{
//if(p_graf)
//    p_graf->setVal( 310.0 );
}



