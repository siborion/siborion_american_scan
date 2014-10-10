#include "CheckBoxDelegate1.h"


CheckBoxDelegate1::CheckBoxDelegate1(QObject *parent)
{

}

//void CheckBoxDelegate1::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//bool checkValue;

//QStyleOptionButton BtnStyle;
//BtnStyle.state = QStyle::State_Enabled;

//if(index.model()->data(index, Qt::DisplayRole).toBool() == true)
//{
//BtnStyle.state |= QStyle::State_On;
//checkValue = true;
//}else{
//BtnStyle.state |= QStyle::State_Off;
//checkValue = false;
//}


//BtnStyle.direction = QApplication::layoutDirection();
//BtnStyle.rect = option.rect;
//QApplication::style()->drawControl(QStyle::CE_CheckBox,&BtnStyle,painter );
//QApplication::style()->drawControl(QStyle::CE_CheckBox,&BtnStyle,painter );
//}

void CheckBoxDelegate1::changed( bool value )
{
    BooleanWidget *checkbox = static_cast<BooleanWidget*>( sender() );
    emit commitData( checkbox );
    emit closeEditor( checkbox );
}

QWidget *CheckBoxDelegate1::createEditor( QWidget *parent,const QStyleOptionViewItem &/* option */,const QModelIndex &/* index */ ) const
{
  BooleanWidget *editor = new BooleanWidget( parent );
//  connect( editor, SIGNAL( toggled ( bool ) ), this, SLOT( changed( bool ) ) );
  return editor;
}

void CheckBoxDelegate1::setEditorData( QWidget *editor,const QModelIndex &index ) const
{
    int value = index.model()->data(index, Qt::DisplayRole).toInt();
    BooleanWidget *checkbox = static_cast<BooleanWidget*>(editor);
    if(value == 1)
        checkbox->setChecked(true);
    else
        checkbox->setChecked(false);
}

void CheckBoxDelegate1::setModelData( QWidget *editor,QAbstractItemModel *model,const QModelIndex &index ) const
{
    BooleanWidget *checkBox = qobject_cast<BooleanWidget*>( editor );
    Qt::CheckState value;
    if(checkBox->isChecked())
        value = Qt::Checked;
    else
        value = Qt::Unchecked;
    model->setData( index, value, Qt::DisplayRole);
}

void CheckBoxDelegate1::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
    drawFocus(painter, option, option.rect);
}
