#ifndef LISTRESULT_H
#define LISTRESULT_H

#include <QDialog>
#include <adjview.h>
#include "curparam.h"

namespace Ui {
class ListResult;
}

class ListResult : public QDialog
{
    Q_OBJECT

public:
    explicit ListResult(QWidget *parent = 0, CurParam *link = 0);
    ~ListResult();
    adjview *twListResult;

private:
    Ui::ListResult *ui;
    CurParam *curParam;
};

#endif // LISTRESULT_H
