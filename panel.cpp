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
    setStyleSheet("QTabBar::tab { min-width: 100px; }");
    setTabPosition( QTabWidget::North );
    addTab( createMesTab( this ), "MEASUREMENT" );
    addTab( createOnlineTab( this ), "IOL CALCULATOR" );
    addTab( createBaseTab( this ), "BASE" );
}

QWidget *Panel::createOnlineTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
//    QGridLayout *layout = new QGridLayout( page );
//    ScanPlot *p_scan = new ScanPlot();
//    layout->addWidget( p_scan, 0, 0 );
    return page;
}

QWidget *Panel::createBaseTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    return page;
}

mesurement *Panel::createMesTab( QWidget *parent )
{
    mesurement *Mesur = new mesurement(parent);
    return Mesur;
}



