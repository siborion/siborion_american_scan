#ifndef PRINTPLOT_H
#define PRINTPLOT_H
#include "plot.h"

class PrintPlot: public QwtPlot
{
Q_OBJECT

public:
    PrintPlot();

private:
    Plot *pPlotPrint;
};

#endif // PRINTPLOT_H
