#ifndef MYDELEGATE_H
#define MYDELEGATE_H
#include <QItemDelegate>
#include <QModelIndex>
#include <QDateEdit>
#include <QPainter>
#include <QIdentityProxyModel>

class mydelegate : public QItemDelegate {
        Q_OBJECT
    public:
        mydelegate(bool calpopup = true,
                     QObject *parent = 0);
        QWidget *createEditor(
                    QWidget *parent,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
        void setEditorData(QWidget *editor,
                           const QModelIndex &index) const;
        void setModelData(QWidget *editor,
                          QAbstractItemModel *model,
                          const QModelIndex &index) const;
        void updateEditorGeometry(
                QWidget *editor,
                const QStyleOptionViewItem &option,
                const QModelIndex &index) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;
    private:
        bool m_calpopup;
    };

#endif // MYDELEGATE_H
