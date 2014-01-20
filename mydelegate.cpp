#include "mydelegate.h"

mydelegate::mydelegate(bool calpopup, QObject *parent)
    : QItemDelegate(parent),
      m_calpopup(calpopup)
{
}

QWidget *mydelegate::createEditor(
        QWidget *parent,
        const QStyleOptionViewItem& option ,
        const QModelIndex& index) const
{
//    QDateEdit *editor = new QDateEdit(parent);
//    editor->setCalendarPopup(m_calpopup);
//    editor->installEventFilter(const_cast<mydelegate*>(this));
//    return editor;
    return QItemDelegate::createEditor(parent, option, index);
}

void mydelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index) const
{
//    QDate value = index.model()->data(
//                index, Qt::EditRole).toDate();
//    QDateEdit *de = static_cast<QDateEdit*>(editor);
//    de->setDate(value);
//    QLineEdit *de = static_cast<QLineEdit*>(editor);
//    de->setDate(value);
      QItemDelegate::setEditorData(editor, index);
}

void mydelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex& index) const
{
//    QDateEdit *de = static_cast<QDateEdit*>(editor);
//    de->interpretText();
//    QDate value = de->date();
//    model->setData(index, value);
    QItemDelegate::setModelData(editor, model, index);
}

void mydelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex& index) const
{
//    editor->setGeometry(option.rect);
    QItemDelegate::updateEditorGeometry(editor, option, index);
}

void mydelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const
{
    QStyleOptionViewItem o = option;
//    o.font.setBold(true);

    if((index.row()==0)||(index.row()==2))
        painter->fillRect(o.rect, QColor(255, 170, 255));

    if(index.data(Qt::DisplayRole).toInt()==1)
        painter->fillRect(o.rect, Qt::green);

    QItemDelegate::paint(painter, o, index);

//    index.data(Qt::DisplayRole).toInt()=1

    //    if(index.row()==0)
    //        painter->fillRect(option.rect, Qt::red);
    //    else
    //        painter->fillRect(option.rect, QColor(200, 200, 200));
    //    QItemDelegate::paint(painter, option, index);
}



