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
    ~CalcLensTable();

private:
    Ui::CalcLensTable *ui;
    QAbstractItemModel *tableModel;
};

#endif // CALCLENSTABLE_H
