#ifndef CALCLENSTABLE_H
#define CALCLENSTABLE_H

#include <QTableView>
#include "combo_delegate_cell.h"
#include   "adjview.h"
#include "calc.h"

namespace Ui {
class CalcLensTable;
}

class CalcLensTable : public adjview
{
    Q_OBJECT

public:
//    explicit CalcLensTable(adjview *);
    explicit CalcLensTable(int row, int col, QList<int> pr, QTableView *parent);
    void setValue(quint8 nomLens, quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal);
    ~CalcLensTable();

private:
    virtual void mousePressEvent(QMouseEvent *event);
    QList <CCombo_Delegate_Cell*> pCombo_Delegate;
    Ui::CalcLensTable *ui;
    QAbstractItemModel *tableModel;
    void setSide(QString val);
    QStringList getListFormula();
    void calculateIOL(quint8 nomLens, quint8 formula);
    void refreshFormula(quint8 nomLens, int curIndex);
    void saveParam(quint8 nomLens, _formulae *val);

    double AL[5];
    double K[5];
    double AConst[5];
    double ACD[5];
    double SF[5];
    double A0[5];
    double A1[5];
    double A2[5];
    double ACD_measure[5];
    double Rx[5];

private slots:
    void changeFotmula(quint8 nomLens, int);
    void slChangeCombo1();
    void slChangeCombo2();
    void slChangeCombo3();
    void slChangeCombo4();
    void slChangeCombo5();


};

#endif // CALCLENSTABLE_H
