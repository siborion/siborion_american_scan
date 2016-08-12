#include <QtWidgets>
#include "delegateprint.h"

DelegatePrint::DelegatePrint(QObject *parent)
    : QItemDelegate(parent)
{
}

void DelegatePrint::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    //     drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
    QImage img;

    if(index.data().toBool())
        img.load(":/test/print");
    else
        img.load(":/test/print_dis");
    //     img.scaledToHeight(10);
   // qDebug()<<img.size();


    //     img.

    //     painter->drawImage(painter->viewport(),img);
    painter->drawImage(option.rect, img);

    //     painter->drawPicture(painter->viewport(),
    //     drawFocus(painter, option, option.rect);
}

//QWidget *DelegatePrint::createEditor(QWidget *parent,
//                                     const QStyleOptionViewItem &/* option */,
//                                     const QModelIndex &/* index */) const
//{
//    QCheckBox *editor = new QCheckBox(parent);
//    return editor;
//}

//void DelegatePrint::setEditorData(QWidget *editor,
//                                  const QModelIndex &index) const
//{
//    int value = index.model()->data(index, Qt::EditRole).toInt();
//    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//    CheckBox->setChecked(value);
//}

//void DelegatePrint::setModelData(QWidget *editor, QAbstractItemModel *model,
//                                 const QModelIndex &index) const
//{
//    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//    int value = CheckBox->isChecked();
//    model->setData(index, value, Qt::EditRole);
//}

//void DelegatePrint::updateEditorGeometry(QWidget *editor,
//                                         const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//    editor->setGeometry(option.rect);
//}

