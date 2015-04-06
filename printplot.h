#ifndef PRINTPLOT_H
#define PRINTPLOT_H
#include "plot.h"
#include "curparam.h"
class PrintPlot: public Plot
{
Q_OBJECT
public:
    PrintPlot(QWidget*, CurParam*, QByteArray*);
private:
};
#endif // PRINTPLOT_H
