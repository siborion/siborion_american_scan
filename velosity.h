#ifndef VELOSITY_H
#define VELOSITY_H

#include <QWidget>
#include "scanbutton.h"

namespace Ui {
class Velosity;
}

class Velosity : public QWidget
{
    Q_OBJECT

public:
    explicit Velosity(QWidget *parent = 0);
    ~Velosity();

private:
    Ui::Velosity *ui;
    ScanButton    *pbMeasure;

private slots:
    void doScanSlot(bool*);
    void doStopSlot();

signals:
    void doScan(bool*);
    void doStop();


};

#endif // VELOSITY_H
