#ifndef BIGVIEWNUMCUR_H
#define BIGVIEWNUMCUR_H

#include "typedef.h"
#include <QWidget>
#include <QDate>

namespace Ui {
class Bigviewnumcur;
}

class Bigviewnumcur : public QWidget
{
    Q_OBJECT
    
public:
    explicit Bigviewnumcur(QWidget *parent = 0);
    ~Bigviewnumcur();
private:
    Ui::Bigviewnumcur *ui;

public slots:
    void setDisplay(stMeasureParam *);
};

#endif // bigviewnumcur_H
