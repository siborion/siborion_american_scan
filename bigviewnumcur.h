#ifndef BIGVIEWNUMCUR_H
#define BIGVIEWNUMCUR_H

#include <QWidget>
#include <QDate>

namespace Ui {
class bigviewnumcur;
}

class bigviewnumcur : public QWidget
{
    Q_OBJECT
    
public:
    explicit bigviewnumcur(QWidget *parent = 0);
    ~bigviewnumcur();
    void setDisplay(double AL, double ACD, double LT, double VIT);
    void setPatient(QString FIO);
    void setDoctor(QString FIO);
    void changeEye(quint8);
private:
    Ui::bigviewnumcur *ui;
};

#endif // bigviewnumcur_H
