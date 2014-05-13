#ifndef __COMBO_DELEGATE_H__
#define __COMBO_DELEGATE_H__

#include <QItemDelegate>

class CCombo_Delegate : public QItemDelegate
{
    Q_OBJECT;
    QHash<int, QString> m_values;

public:
    CCombo_Delegate( QObject * parent = 0 );
    QWidget * createEditor( QWidget * parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;
    void setEditorData( QWidget * editor, const QModelIndex &index ) const;
    void setModelData( QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index ) const;
    void updateEditorGeometry( QWidget *editor,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;
    void paint( QPainter * painter, const QStyleOptionViewItem &option,
                const QModelIndex &index ) const;

    inline QHash<int, QString>& values() { return m_values; }
};

#endif // __COMBO_DELEGATE_H__
