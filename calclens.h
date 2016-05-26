#ifndef CALCLENS_H
#define CALCLENS_H

#include <QFrame>
#include <QGridLayout>
#include "calclenstable.h"

namespace Ui {
class CalcLens;
}

class CalcLens : public QFrame
{
    Q_OBJECT

public:
    explicit CalcLens(QWidget *parent = 0);
    ~CalcLens();

private:
    Ui::CalcLens *ui;
    QGridLayout   *gridLayout;
    CalcLensTable *lensTable;
};

#endif // CALCLENS_H
