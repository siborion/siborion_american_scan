#ifndef BIGVIEWNUM_H
#define BIGVIEWNUM_H

#include <QWidget>

namespace Ui {
class bigviewnum;
}

class bigviewnum : public QWidget
{
    Q_OBJECT
    
public:
    explicit bigviewnum(QWidget *parent = 0);
    ~bigviewnum();
    void setDisplay(double Al);
    void setDisplay(double Al, double Avg, double Div);
    void setDisplay(double Avg, double AvgAcd, double AvgLt, double AvgVit, double Dev, double DevAcd, double DevLt, double DevVit);
    
private:
    Ui::bigviewnum *ui;
};

#endif // BIGVIEWNUM_H
