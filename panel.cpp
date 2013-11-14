#include "panel.h"
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
    QGridLayout *layout = new QGridLayout( page );
    ScanPlot *p_scan = new ScanPlot();
    layout->addWidget( p_scan, 0, 0 );

    return page;
}

QWidget *Panel::createBaseTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    return page;
}


