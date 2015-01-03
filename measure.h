#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "plot.h"


class Measure : public QWidget
{
    Q_OBJECT
public:
    explicit Measure(QWidget *parent = 0);

private:
    Plot *pPlot;

signals:

public slots:

};

#endif // MEASURE_H
