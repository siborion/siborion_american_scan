#ifndef DELEGATEPRINT_H
#define DELEGATEPRINT_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QCheckBox>

 class DelegatePrint : public QItemDelegate
 {
     Q_OBJECT
 public:
     DelegatePrint(QObject *parent = 0);
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;
     void paint(QPainter *painter, const QStyleOptionViewItem &option,
                const QModelIndex &index) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;
     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
 };

 #endif
