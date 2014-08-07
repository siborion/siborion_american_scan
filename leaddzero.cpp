#include "leaddzero.h"

leAddZero::leAddZero(QWidget *parent) :
    QLineEdit(parent)
{
        connect(this, SIGNAL(editingFinished()), SLOT(lineEditUpdate()));
}

void leAddZero::lineEditUpdate()
{
    float val;
//    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    val = this->text().toFloat();
    this->setText(QString("%1").arg(val, 0, 'f', 2));
}


