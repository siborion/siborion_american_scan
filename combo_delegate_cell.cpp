#include "combo_delegate_cell.h"

#include <QPainter>
#include <comboitem.h>
#include <QLineEdit>
#include <QDebug>

CCombo_Delegate_Cell::CCombo_Delegate_Cell( QObject *parent ) : QItemDelegate(parent)
{
}

QWidget * CCombo_Delegate_Cell::createEditor( QWidget * parent,
                                      const QStyleOptionViewItem&  option ,
                                      const QModelIndex&  index ) const
{
    if(index.row()==1)
    {
        quint8 k=0;
        QFont font;
        ComboItem * pEditor = new ComboItem( parent );
        pEditor->setFrame(false);
        font.setBold(true);
        pEditor->setFont(font);
        QHash<int, QString>::const_iterator i = m_values.constBegin();
        while ( i != m_values.constEnd() )
        {
            pEditor -> addItem( i.value(), i.key() );
            pEditor->setItemData(k,Qt::AlignCenter, Qt::TextAlignmentRole);
            ++i;
            k++;
        }
        pEditor->model()->sort(0);
        pEditor -> installEventFilter( const_cast<CCombo_Delegate_Cell*>( this ) );
        if(pEditor->lineEdit())
            pEditor->lineEdit()->setAlignment(Qt::AlignHCenter);
//        pEditor->showPopup();
        return pEditor;
    }
    else
    {
//        QLineEdit * pEditor = new QLineEdit( parent );
//        return pEditor;
        return 0;
    }
}

void CCombo_Delegate_Cell::setEditorData( QWidget * editor, const QModelIndex &index) const
{
    if(index.row()==1)
    {
        int value = index.model()->data( index, Qt::EditRole ).toInt();
        ComboItem * cb = static_cast<ComboItem*>( editor );
        int idx = cb->findData( value );
        if ( idx < 0 ) return;
        cb->setCurrentIndex( idx );
//        cb->showPopup();
    }
    else
    {
//        QLineEdit * le = static_cast<QLineEdit*>( editor );
//        QString value = index.model()->data( index, Qt::EditRole ).toString();
//        le->setText(value);
    }
}

void CCombo_Delegate_Cell::setModelData( QWidget * editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex& index) const
{
    if(index.row()==1)
    {
        ComboItem * cb = static_cast<ComboItem*>( editor );
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

    if(index.row()==1)
    {
        int value = index.data().toInt();
        s = m_values[ value ];
    }
    else
        s = index.data(Qt::DisplayRole).toString();


    opt.displayAlignment = (Qt::Alignment)index.data(Qt::TextAlignmentRole).toUInt();//   Qt::AlignVCenter | Qt::AlignHCenter;\


    QVariant value;
    QFont font;
    value = index.data(Qt::FontRole);
    if (value.canConvert<QFont>())
    {
        font = qvariant_cast<QFont>(value);
        opt.font.setBold(font.bold());
    }

    drawBackground(painter, opt, index);

    if((index.row()==1) && ((opt.state & QStyle::State_Editing)==0))
    {
        ComboItem cb;
        cb.setFrame(false);
        cb.setMaximumSize(opt.rect.size());
        cb.setMinimumSize(opt.rect.size());
        QPixmap pm(cb.size());
        cb.render(&pm, QPoint(0,0));
        painter->drawPixmap(opt.rect.topLeft(),pm);
    }

//    drawDecoration(painter, opt, decorationRect, pixmap);
//    drawDecoration(painter, opt, decorationRect, pm);
    drawDisplay(painter, opt, opt.rect, s);
    drawFocus(painter, opt, opt.rect);
}
