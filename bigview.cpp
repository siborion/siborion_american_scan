#include "bigview.h"

bigview::bigview(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    lcdNumber = new QLCDNumber();
    layout->addWidget(lcdNumber);
    lcdNumber->display("00.00");
}

void bigview::setDisplay(double num)
{
    lcdNumber->display(num);
}
