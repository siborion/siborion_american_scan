#ifndef BIGVIEWNUM_H
#define BIGVIEWNUM_H

#include <QWidget>
#include "typedef.h"
#include "curparam.h"

namespace Ui {
class bigviewnum;
}

class bigviewnum : public QWidget
{
    Q_OBJECT
    
public:
    explicit bigviewnum(QWidget *parent = 0,  CurParam *Link=0);
    ~bigviewnum();
//    void setDisplay(double Al, double Avg, double Div);
    void setDisplay();
    
private:
    Ui::bigviewnum *ui;
    CurParam *curParam;

public slots:
    void setDisplay(stAverageParam*);
    void setRegim();
};

#endif // BIGVIEWNUM_H
