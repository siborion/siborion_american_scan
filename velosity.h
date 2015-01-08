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

signals:
    void doScan(bool*);


};

#endif // VELOSITY_H
