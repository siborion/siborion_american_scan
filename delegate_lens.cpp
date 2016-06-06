#include <QtWidgets>
#include "delegate_lens.h"

 DelegateLens::DelegateLens(QObject *parent)
     : QItemDelegate(parent)
 {
 }

// void DelegateLens::paint(QPainter *painter, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const
// {
//     drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
////     drawFocus(painter, option, option.rect);
// }

// QWidget *DelegateLens::createEditor(QWidget *parent,
//     const QStyleOptionViewItem &/* option */,
//     const QModelIndex &/* index */) const
// {
//     QCheckBox *editor = new QCheckBox(parent);

//     return editor;
// }

// void DelegateLens::setEditorData(QWidget *editor,
//                                     const QModelIndex &index) const
// {
//     int value = index.model()->data(index, Qt::EditRole).toInt();
//     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//     CheckBox->setChecked(value);

// }

// void DelegateLens::setModelData(QWidget *editor, QAbstractItemModel *model,
//                                    const QModelIndex &index) const
// {
//     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
//     int value = CheckBox->isChecked();
//     model->setData(index, value, Qt::EditRole);
// }

// void DelegateLens::updateEditorGeometry(QWidget *editor,
//     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
// {
//     editor->setGeometry(option.rect);

// }


 QVariant DelegateLens::data(const QModelIndex& index, int role) const
 {
      if (!index.isValid()) {
         return QVariant();
      }
      if (role == Qt::BackgroundRole) {
          if (1==1) {
                 return QBrush(Qt::green);
          } else {
              return QVariant();
          }
      }
      return DelegateLens::data(index, role);
 }
