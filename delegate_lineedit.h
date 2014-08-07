#ifndef DELEGATE_LINEEDIT_H
#define DELEGATE_LINEEDIT_H
#include <QLineEdit>
#include <QItemDelegate>
#include <QStyledItemDelegate>

//! [0]
class delegate_lineedit : public QStyledItemDelegate
{
    Q_OBJECT

public:
    delegate_lineedit(QObject *parent = 0);

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                                       const QModelIndex &index) const;


//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const;

//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                      const QModelIndex &index) const;

//    void updateEditorGeometry(QWidget *editor,
//        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};



#endif // DELEGATE_LINEEDIT_H
