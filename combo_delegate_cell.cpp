#include "Combo_Delegate_Cell.h"

#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

CCombo_Delegate_Cell::CCombo_Delegate_Cell( QObject *parent ) : QItemDelegate(parent)
{
}

QWidget * CCombo_Delegate_Cell::createEditor( QWidget * parent,
                                      const QStyleOptionViewItem&  option ,
                                      const QModelIndex&  index ) const
{
    if(index.row()==2)
    {
        QComboBox * pEditor = new QComboBox( parent );
        QHash<int, QString>::const_iterator i = m_values.constBegin();
        while ( i != m_values.constEnd() )
        {
            pEditor -> addItem( i.value(), i.key() );
            ++i;
        }
        pEditor->model()->sort(0);
        pEditor -> installEventFilter( const_cast<CCombo_Delegate_Cell*>( this ) );
        return pEditor;
    }
    else
    {
        QLineEdit * pEditor = new QLineEdit( parent );
        return pEditor;
    }
}

void CCombo_Delegate_Cell::setEditorData( QWidget * editor, const QModelIndex &index) const
{
    if(index.row()==2)
    {
        int value = index.model()->data( index, Qt::EditRole ).toInt();
        QComboBox * cb = static_cast<QComboBox*>( editor );
        int idx = cb->findData( value );
        if ( idx < 0 ) return;
        cb->setCurrentIndex( idx );
    }
    else
    {
        QLineEdit * le = static_cast<QLineEdit*>( editor );
        QString value = index.model()->data( index, Qt::EditRole ).toString();
        le->setText(value);
    }
}

void CCombo_Delegate_Cell::setModelData( QWidget * editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex& index) const
{
    if(index.row()==2)
    {
        QComboBox * cb = static_cast<QComboBox*>( editor );
        int idx = cb->currentIndex();
        if ( idx < 0 ) return;
        int value = cb->itemData( idx ).toInt();
        model->setData( index, value );
    }
    else
    {
        QLineEdit *le =  static_cast<QLineEdit*>( editor );
        model->setData(index, le->text());
    }
}

void CCombo_Delegate_Cell::updateEditorGeometry( QWidget *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex& /* index */) const
{
    editor->setGeometry( option.rect );
}

void CCombo_Delegate_Cell::paint( QPainter * painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index ) const
{
    QString s;

    QStyleOptionViewItem opt = option;

    if(index.row()==2)
    {
        int value = index.data().toInt();
        s = m_values[ value ];
    }
    else
        s = index.data(Qt::DisplayRole).toString();
    QVariant color = index.data( Qt::TextColorRole );
    if ( color.isValid() && qvariant_cast<QColor>(color).isValid() )
        opt.palette.setColor( QPalette::Text, qvariant_cast<QColor>(color) );
    color = index.data( Qt::BackgroundColorRole);
    if ( color.isValid() && qvariant_cast<QColor>(color).isValid() )
    {
        qDebug()<<color;
        opt.palette.setColor( QPalette::Base, qvariant_cast<QColor>(color) );
//        opt.palette.setColor(Qt::BackgroundColorRole, qvariant_cast<QColor>(color));
//          opt.palette.setColor()
    }
//    opt.displayAlignment = Qt::AlignVCenter | Qt::AlignLeft;




    if (option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
        QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
                ? QPalette::Normal : QPalette::Disabled;
        if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
            cg = QPalette::Inactive;

        painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Highlight));
    } else {
        QVariant value = index.data(Qt::BackgroundRole);
        if (value.canConvert<QBrush>()) {
            QPointF oldBO = painter->brushOrigin();
            painter->setBrushOrigin(option.rect.topLeft());
            painter->fillRect(option.rect, qvariant_cast<QBrush>(value));
            painter->setBrushOrigin(oldBO);
        }
    }





    drawDisplay(painter, opt, opt.rect, s);
    drawFocus(painter, opt, opt.rect);
}
