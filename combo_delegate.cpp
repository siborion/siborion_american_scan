#include "Combo_Delegate.h"

#include <QPainter>
#include <QComboBox>

CCombo_Delegate::CCombo_Delegate( QObject *parent ) : QItemDelegate(parent)
{
}

QWidget * CCombo_Delegate::createEditor( QWidget * parent,
                                      const QStyleOptionViewItem& /* option */,
                                      const QModelIndex& /* index */) const
{
    QComboBox * pEditor = new QComboBox( parent );

    QHash<int, QString>::const_iterator i = m_values.constBegin();
    while ( i != m_values.constEnd() )
    {
        pEditor -> addItem( i.value(), i.key() );
        ++i;
     }

    pEditor -> installEventFilter( const_cast<CCombo_Delegate*>( this ) );
    return pEditor;
}

void CCombo_Delegate::setEditorData( QWidget * editor, const QModelIndex &index) const
{
    int value = index.model()->data( index, Qt::EditRole ).toInt();
    QComboBox * cb = static_cast<QComboBox*>( editor );

    int idx = cb->findData( value );
    if ( idx < 0 ) return;
    cb->setCurrentIndex( idx );
}

void CCombo_Delegate::setModelData( QWidget * editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex& index) const
{
    QComboBox * cb = static_cast<QComboBox*>( editor );
    int idx = cb->currentIndex();
    if ( idx < 0 ) return;
    int value = cb->itemData( idx ).toInt();
    model->setData( index, value );
}

void CCombo_Delegate::updateEditorGeometry( QWidget *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex& /* index */) const
{
    editor->setGeometry( option.rect );
}

void CCombo_Delegate::paint( QPainter * painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index ) const
{
    QStyleOptionViewItem opt = option;
    int value = index.data().toInt();


    QString s = m_values[ value ];
    QVariant color = index.data( Qt::TextColorRole );

    if ( color.isValid() && qvariant_cast<QColor>(color).isValid() )
        opt.palette.setColor( QPalette::Text, qvariant_cast<QColor>(color) );

    opt.displayAlignment = Qt::AlignVCenter | Qt::AlignLeft;

    drawDisplay(painter, opt, opt.rect, s);
    drawFocus(painter, opt, opt.rect);
}
