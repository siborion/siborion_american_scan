#include "leaddzero.h"

leAddZero::leAddZero(QWidget *parent) :
    QLineEdit(parent)
{
    this->setMinimumWidth(50);
        connect(this, SIGNAL(editingFinished()), SLOT(lineEditUpdate()));
}

void leAddZero::setTextZero(QString sVal)
{
    this->setText(sVal);
    emit(editingFinished());
//    lineEditUpdate();
}

void leAddZero::lineEditUpdate()
{
    float val;
    val = this->text().toFloat();
    this->setText(QString("%1").arg(val, 5, 'f', 2, '0'));
}

void leAddZero::lineEditRefresh()
{
    lineEditUpdate();
}
