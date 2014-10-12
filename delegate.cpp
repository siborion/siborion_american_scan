#include <QtGui>
#include "delegate.h"

 CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
     : QItemDelegate(parent)
 {
 }

 void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
 {
     drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
//     drawFocus(painter, option, option.rect);
     qDebug()<<"edit0";
 }

 QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex &/* index */) const
 {
     QCheckBox *editor = new QCheckBox(parent);
     qDebug()<<"edit1";
     return editor;
 }

 void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     int value = index.model()->data(index, Qt::EditRole).toInt();
     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
     CheckBox->setChecked(value);
     qDebug()<<"edit2";
 }

 void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
     int value = CheckBox->isChecked();
     model->setData(index, value, Qt::EditRole);
     qDebug()<<"edit3";
 }

 void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
     qDebug()<<"edit4";
 }

