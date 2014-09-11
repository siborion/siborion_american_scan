#ifndef LINESELECT_H
#define LINESELECT_H

#include <QWidget>

namespace Ui {
class LineSelect;
}

class LineSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LineSelect(QWidget *parent = 0);
    ~LineSelect();

private:
    Ui::LineSelect *ui;
};

#endif // LINESELECT_H
