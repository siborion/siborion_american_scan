#ifndef BListResult_H
#define BListResult_H

#include <QDialog>
#include <adjview.h>
#include "curparam.h"

namespace Ui {
class BListResult;
}

class BListResult : public QDialog
{
    Q_OBJECT

public:
    explicit BListResult(QWidget *parent = 0, CurParam *link = 0);
    ~BListResult();
    adjview *twBListResult;

private:
    Ui::BListResult *ui;
    CurParam *curParam;
};

#endif // BListResult_H
