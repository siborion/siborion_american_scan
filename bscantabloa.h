#ifndef BSCANTABLOA_H
#define BSCANTABLOA_H

#include <QWidget>

namespace Ui {
class BScanTabloA;
}

class BScanTabloA : public QWidget
{
    Q_OBJECT

public:
    explicit BScanTabloA(QWidget *parent = 0);
    ~BScanTabloA();

private:
    Ui::BScanTabloA *ui;
};

#endif // BSCANTABLOA_H
