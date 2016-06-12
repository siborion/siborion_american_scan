#ifndef PRINT_H
#define PRINT_H

#include "typedef.h"
#include <QWidget>
#include "adjview.h"
#include "plot.h"
#include "printplot.h"
#include "qtrpt.h"
#include "formula.h"

class Print : public QWidget
{
    Q_OBJECT
public:
    explicit Print(QWidget *parent = 0, CurParam *link=0);
    adjview *twMeas;
//    QAbstractItemModel *Formila1;
//    QAbstractItemModel *Formila2;
//    QAbstractItemModel *Formila3;
    formula *Formila1;
    formula *Formila2;
    formula *Formila3;
    void doPreview();
private:
    double al1, al2, al3, al4, acd1, acd2, acd3, acd4;
    QImage iPlot1, iPlot2, iPlot3, iPlot4;
    PrintPlot *pPlotPrint1;
    Plot *pPlotPrint2;
    Plot *pPlotPrint3;
    Plot *pPlotPrint4;
    CurParam *curParam;
    QtRPT *report    ;



signals:

public slots:

private slots:
    void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
    void setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage);
};

#endif // PRINT_H
