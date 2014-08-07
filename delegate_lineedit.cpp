#include "delegate_lineedit.h"

delegate_lineedit::delegate_lineedit(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


//QWidget *delegate_lineedit::createEditor(QWidget *parent,
//    const QStyleOptionViewItem &/* option */,
//    const QModelIndex &/* index */) const
//{
//    QLineEdit *lineEdit = new QLineEdit(parent);

//    return editor;
//}

//void delegate_lineedit::setEditorData(QWidget *editor,
//                                    const QModelIndex &index) const
//{
//    QString value = index.model()->data(index, Qt::EditRole).toString();

//    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    lineEdit->setText(value);
//}

void delegate_lineedit::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
////    lineEdit->returnPressed();
    QString value = lineEdit->text();

    model->setData(index, value, Qt::EditRole);
}

//void delegate_lineedit::updateEditorGeometry(QWidget *editor,
//    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//    editor->setGeometry(option.rect);
//}
