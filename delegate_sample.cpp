#include "delegate_sample.h"
#include <QCheckBox>
#include <QDebug>
#include <QPainter>

delegate_sample::delegate_sample(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void delegate_sample::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    qDebug()<<"row"<<index.row();
    qDebug()<<"column"<<index.column();
    if(index.model()->index(index.row(), 1).data(Qt::UserRole).toDouble() > 0.2)
        painter->fillRect(option.rect, QColor(Qt::yellow));
    else
        painter->fillRect(option.rect, QColor(Qt::white));
    QStyledItemDelegate::paint(painter, option, index);
}

//QWidget *delegate_sample::createEditor(QWidget *parent,
//    const QStyleOptionViewItem &/* option */,
//    const QModelIndex &/* index */) const
//{
//    if(QModelIndex.column()==0)
//        QCheckBox *editor = new QCheckBox(parent);
//    return editor;
//    return parent;
//}

//void delegate_sample::setEditorData(QWidget *editor,
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

//void delegate_sample::setModelData(QWidget *editor, QAbstractItemModel *model,
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

//void delegate_sample::updateEditorGeometry(QWidget *editor,
//    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//    editor->setGeometry(option.rect);
//}
