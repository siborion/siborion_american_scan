#include "panel.h"
//#include "scanplot.h"
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
//    QPalette Pal(palette());
//    Pal.setColor(QPalette::Background, Qt::gray);
//    setAutoFillBackground(true);
//    setPalette(Pal);

    page = new bases( parent );
    Mesur = new mesurement(parent);
    Calculator = new calculator(parent);

    setStyleSheet("QTabBar::tab { min-width: 100px; }");
    setTabPosition( QTabWidget::North );
//    addTab( createBaseTab( this ), "Data Base" );
    addTab( page, "Data Base" );
//    addTab( createMesTab( this ), "Measurement" );
    addTab( Mesur, "Measurement" );
//    addTab( createHisTab( this ), "History" );
    addTab( Calculator, "Calculator" );
    addTab( createOnlineTab( this ), "Print" );
    connect(page,SIGNAL(changeRow(quint8,quint16,QString,QString)),Mesur,SLOT(changeRow(quint8,quint16,QString,QString)));
    connect(page,SIGNAL(changeRow(quint8,quint16,QString,QString)),Calculator,SLOT(changeRow(quint8,quint16,QString,QString)));
    connect(Mesur,SIGNAL(refreshMeasure(stMeasureParam)),Calculator,SLOT(refreshMeasure(stMeasureParam)));
    connect(Mesur,SIGNAL(refreshAcd(double)),Calculator,SLOT(refreshAcd(double)));


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


