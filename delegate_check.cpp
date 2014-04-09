#include "delegate_check.h"
#include <QCheckBox>
#include <QDebug>
#include <QPainter>

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if(index.model()->index(index.row(), 0).data(Qt::DisplayRole) == 1)
        painter->fillRect(option.rect, QColor(Qt::green));
    QStyledItemDelegate::paint(painter, option, index);
}

//QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
//    const QStyleOptionViewItem &/* option */,
//    const QModelIndex &/* index */) const
//{
//    if(QModelIndex.column()==0)
//        QCheckBox *editor = new QCheckBox(parent);
//    return editor;
//    return parent;
//}

//void CheckBoxDelegate::setEditorData(QWidget *editor,
//                                     const QModelIndex &index) const
//{
//    qDebug()<<index.column();
//    if(index.column()==0)
//    {
//        int value = index.model()->data(index, Qt::EditRole).toInt();
//        QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//        CheckBox->setChecked(value);
//    }
//}

//void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
//                                   const QModelIndex &index) const
//{
//    qDebug()<<index.column();
//    if(index.column()==0)
//    {
//        QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//        int value = CheckBox->isChecked();
//        model->setData(index, value, Qt::EditRole);
//    }
//}

//void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
//    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//    editor->setGeometry(option.rect);
//}
