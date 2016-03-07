#ifndef BSCANCONTROL_H
#define BSCANCONTROL_H

#include <QWidget>
#include "adjview.h"

namespace Ui {
class BScanControl;
}

class BScanControl : public QWidget
{
    Q_OBJECT

public:
    explicit BScanControl(QWidget *parent = 0);
    ~BScanControl();

private:
    Ui::BScanControl *ui;
    adjview *table;

private slots:
    void changeRow(QModelIndex);

public slots:
    void setArray(unsigned char *buf);

};

#endif // BSCANCONTROL_H
