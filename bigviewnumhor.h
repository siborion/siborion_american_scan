#ifndef bigviewnumhor_H
#define bigviewnumhor_H

#include "ui_bigviewnumhor.h"
#include <QWidget>

namespace Ui {
class bigviewnumhor;
}

class bigviewnumhor : public QWidget
{
    Q_OBJECT
    
public:
    explicit bigviewnumhor(QWidget *parent = 0);
    ~bigviewnumhor();
    void setDisplay(double Al);
    void setDisplay(double Al, double Avg, double Div);
    
private:
    Ui::bigviewnumhor *ui;
};

#endif // bigviewnumhor_H
