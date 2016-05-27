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
    void setValue(quint8 nomLens, quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal);
    ~CalcLens();

private:
    Ui::CalcLens *ui;
    QGridLayout   *gridLayout;
    CalcLensTable *lensTable;
};

#endif // CALCLENS_H
