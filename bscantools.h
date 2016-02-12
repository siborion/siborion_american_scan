#ifndef BSCANTOOLS_H
#define BSCANTOOLS_H

#include <QWidget>

namespace Ui {
class BScanTools;
}

class BScanTools : public QWidget
{
    Q_OBJECT

public:
    explicit BScanTools(QWidget *parent = 0);
    ~BScanTools();

private:
    Ui::BScanTools *ui;
};

#endif // BSCANTOOLS_H
