#ifndef BUTTONSCAN_H
#define BUTTONSCAN_H

#include <QWidget>

namespace Ui {
class ButtonScan;
}

class ButtonScan : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonScan(QWidget *parent = 0);
    ~ButtonScan();

private:
    Ui::ButtonScan *ui;
};

#endif // BUTTONSCAN_H
