#ifndef BIGVIEWNUMCUR_H
#define BIGVIEWNUMCUR_H

#include <QWidget>

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
private:
    Ui::bigviewnumcur *ui;
};

#endif // bigviewnumcur_H
