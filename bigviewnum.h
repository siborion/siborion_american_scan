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
    void setDisplay(double Avg, double Div);
    
private:
    Ui::bigviewnum *ui;
};

#endif // BIGVIEWNUM_H
