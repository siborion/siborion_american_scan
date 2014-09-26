#include "panel.h"
#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qwt_plot_curve.h>
#include <qwt_slider.h>
#include <qwt_symbol.h>
#include "typedef.h"


Panel::Panel( QWidget *parent ):
    QTabWidget( parent )
{
    page = new bases( parent );
    Mesur = new mesurement(parent);
    Calculator = new calculator(parent);

    setStyleSheet("QTabBar::tab { min-width: 100px; }");
    setTabPosition( QTabWidget::North );
    addTab( page, "Data Base" );
    addTab( Mesur, "Measurement" );
    addTab( Calculator, "Calculator" );
    connect(this, SIGNAL(currentChanged(int)), SLOT(changeTab(int)));
}

QWidget *Panel::createOnlineTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    return page;
}

QWidget *Panel::createBaseTab( QWidget *parent )
{
    bases *page = new bases( parent );
    return page;
}

mesurement *Panel::createMesTab( QWidget *parent )
{
    mesurement *Mesur = new mesurement(parent);
    return Mesur;
}

history *Panel::createHisTab( QWidget *parent )
{
    history *History = new history(parent);
    //    History->setVisible(false);
    return History;
}

calculator *Panel::createCalculatorTab( QWidget *parent )
{
    calculator *Calculator = new calculator(parent);
    return Calculator;
}

void Panel::changeTab(int nomTab)
{
    if(nomTab==2)
    {
        Calculator->refreshMeasure();
        Calculator->refreshFormuls();
    }
}

