#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>

namespace Ui {
class Measure;
}

class Measure : public QWidget
{
    Q_OBJECT

public:
    explicit Measure(QWidget *parent = 0);
    ~Measure();

private:
    Ui::Measure *ui;
};

#endif // MEASURE_H
