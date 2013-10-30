#include <qmainwindow.h>

class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;
class Plot;
class Panel;
class QPolygon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );

private Q_SLOTS:

private:
    Plot *d_plot;
    Panel *d_panel;
};
