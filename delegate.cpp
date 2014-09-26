#include <QtGui>
#include "delegate.h"

 CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
     : QItemDelegate(parent)
 {
 }

 void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
 {
//     if (index.data().canConvert<StarRating>()) {
//         StarRating starRating = qvariant_cast<StarRating>(index.data());

//         if (option.state & QStyle::State_Selected)
//             painter->fillRect(option.rect, option.palette.highlight());

//         starRating.paint(painter, option.rect, option.palette,
//                          StarRating::ReadOnly);
//      else {
//         paint(painter, option, index);
//     }

     QStyleOptionViewItem opt = option;
     int value = index.data().toInt();

     QString s;

     if(value>=1)
         s="V";
     else
         s="-";

//     QString s = m_values[ value ];
//     QVariant color = index.data( Qt::TextColorRole );

//     if ( color.isValid() && qvariant_cast<QColor>(color).isValid() )
//         opt.palette.setColor( QPalette::Text, qvariant_cast<QColor>(color) );

     opt.displayAlignment = Qt::AlignVCenter | Qt::AlignHCenter;
//     QString s = "5";

     drawDisplay(painter, opt, opt.rect, s);

     drawFocus(painter, opt, opt.rect);


 }


 QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &/* option */,
     const QModelIndex &/* index */) const
 {
     QCheckBox *editor = new QCheckBox(parent);

//     editor->setMinimum(0);
//     editor->setMaximum(100);

     return editor;
 }

 void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     int value = index.model()->data(index, Qt::EditRole).toInt();

     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);

     CheckBox->setChecked(value);
 }

 void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
     int value = CheckBox->isChecked();
     model->setData(index, value, Qt::EditRole);
 }

 void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }
