#ifndef BIGVIEWNUMCUR_H
#define BIGVIEWNUMCUR_H

//#include "curentparam.h"
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
    void setDisplay(double AL, double ACD, double LT, double VIT);
//    void setPatient(QString FIO);
//    void setDoctor(QString FIO);
//    void changeEye(quint8);
private:
    Ui::Bigviewnumcur *ui;
//    CurentParam *curentParam;
};

#endif // bigviewnumcur_H
