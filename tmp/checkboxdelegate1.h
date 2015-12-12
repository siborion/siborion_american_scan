#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QItemDelegate>

class BooleanWidget : public QWidget
{
    Q_OBJECT
    QCheckBox * checkBox;
    public:
    BooleanWidget(QWidget * parent = 0)
    {
        Q_UNUSED(parent);
        checkBox = new QCheckBox(this);
        QGridLayout * layout = new QGridLayout(this);
        this->setMaximumHeight(35);
        this->setMinimumHeight(35);
        this->setMaximumWidth(35);
        this->setMinimumWidth(35);
        layout->addWidget(checkBox,0, Qt::AlignHCenter|Qt::AlignVCenter);
    }
    bool isChecked(){return checkBox->isChecked();}
    void setChecked(bool value){checkBox->setChecked(value);}
};

class CheckBoxDelegate1 : public QItemDelegate
{
    Q_OBJECT
private:
    BooleanWidget *checkbox;

public:
    CheckBoxDelegate1(QObject *parent);
//    ~CheckBoxDelegate1();
    void setEditorData( QWidget *editor,const QModelIndex &index )const;
    void setModelData( QWidget *editor,QAbstractItemModel *model,const QModelIndex &index )const;
    QWidget *createEditor( QWidget *parent,const QStyleOptionViewItem &/* option */,const QModelIndex &/* index */ )const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void changed( bool );
};
