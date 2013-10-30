#include "panel.h"
#include "plot.h"
#include "knob.h"
#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qwt_plot_curve.h>

Panel::Panel( QWidget *parent ):
    QTabWidget( parent )
{
    setTabPosition( QTabWidget::North );
    addTab( createOnlineTab( this ), "Online" );
    addTab( createBaseTab( this ), "Base" );
}

QWidget *Panel::createOnlineTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );

    d_amplitudeKnob = new Knob( "Amplitude", 0.0, 200.0, this );
    d_amplitudeKnob->setValue( 160.0 );

    QGridLayout *layout = new QGridLayout( page );
    layout->addWidget( new Plot( page), 0, 0 );
    layout->addWidget( d_amplitudeKnob, 0, 0 );


//    d_plot = new Plot( this );

    return page;
}

QWidget *Panel::createBaseTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    return page;
}


