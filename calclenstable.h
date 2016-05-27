#ifndef CALCLENSTABLE_H
#define CALCLENSTABLE_H

#include <QTableView>
#include   "adjview.h"

namespace Ui {
class CalcLensTable;
}

class CalcLensTable : public adjview
{
    Q_OBJECT

public:
    explicit CalcLensTable(adjview *);
    explicit CalcLensTable(int row, int col, QList<int> pr, QTableView *parent);
    void setValue(quint8 nomLens, quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal);
    ~CalcLensTable();

private:
    Ui::CalcLensTable *ui;
    QAbstractItemModel *tableModel;
    void setSide(QString val);

};

#endif // CALCLENSTABLE_H
