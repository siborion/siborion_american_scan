#include <qregexp.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qpicture.h>
#include <qpainter.h>
#include <qwt_counter.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include "plot.h"
#include "panel.h"
#include "mainwindow.h"

class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( int xAxis, int yAxis, QWidget *canvas ):
        QwtPlotZoomer( xAxis, yAxis, canvas )
    {
        setTrackerMode( QwtPicker::AlwaysOff );
        setRubberBand( QwtPicker::NoRubberBand );
        setMousePattern( QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,Qt::RightButton );
    }
};

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    d_panel = new Panel( this );
//    d_plot = new Plot( this );
//    const int margin = 5;
//    d_plot->setContentsMargins( margin, margin, margin, 0 );

    setCentralWidget( d_panel );

//    setCentralWidget( d_plot );

}


