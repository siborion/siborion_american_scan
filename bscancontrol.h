#ifndef BSCANCONTROL_H
#define BSCANCONTROL_H

#include <QWidget>

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
};

#endif // BSCANCONTROL_H
