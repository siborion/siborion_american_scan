#include "comboitem.h"
#include <QDebug>

ComboItem::ComboItem(QWidget *parent) :
    QComboBox(parent)
{
    connect(this, SIGNAL(currentIndexChanged(int)),SLOT(slClearFocus()));
    connect(this,SIGNAL(activated(int)), SLOT(slPopup()));
//    this->clearFocus();
//    qDebug()<<"00000";
}


void ComboItem::slClearFocus()
{
   this->clearFocus();
}


    void ComboItem::focusInEvent(QFocusEvent *e)
    {
//        qDebug()<<"popup";
//       this->showPopup();
    }

void ComboItem::slPopup()
{
//    qDebug()<<"popup";
//   this->showPopup();
}
