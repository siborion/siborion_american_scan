#ifndef BIGVIEWNUMCUR_H
#define BIGVIEWNUMCUR_H

#include "typedef.h"
#include "curparam.h"
#include <QWidget>
#include <QDate>

namespace Ui {
class Bigviewnumcur;
}

class Bigviewnumcur : public QWidget
{
    Q_OBJECT
    
public:
    explicit Bigviewnumcur(QWidget *parent = 0, CurParam *link = 0);
    ~Bigviewnumcur();
private:
    Ui::Bigviewnumcur *ui;
    CurParam *curParam;

public slots:
    void setDisplay(stMeasureParam *);
    void setRegim();
    void updatePatient();
};

#endif // bigviewnumcur_H
