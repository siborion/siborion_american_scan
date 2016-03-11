#include "bscancontrol.h"
#include "ui_bscancontrol.h"
#include <QDateTime>
#include <QDebug>

BScanControl::BScanControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanControl)
{
    QStringList sl;
    QList<int>  il;
    sl << " ";
    il << 100;

    ui->setupUi(this);

    this->setMaximumWidth(200);

    table            = new adjview(3, sl, il);
    QSpacerItem  *hs = new QSpacerItem(50, 5, QSizePolicy::Maximum, QSizePolicy::Maximum);

    ui->verticalLayout->addWidget(table);
    ui->verticalLayout->addItem(hs);

    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));

    setArray(0);
}

unsigned char *BScanControl::getBuf()
{
    quint8 nomRow;
    quint32 ttt;
    unsigned char *p;
    QModelIndex index;
    nomRow = table->currentIndex().row();
//    qDebug()<<nomRow;
    index = table->model()->index(nomRow,0);
    ttt = table->model()->data(index, Qt::UserRole).toLongLong();
//    qDebug()<<"ttt"<<ttt;
    p = (unsigned char *)ttt;
    return p;
}

void BScanControl::setArray(unsigned char *buf)
{
    QDateTime time;
    QModelIndex indexDest, indexSour;
    quint8 modelSize;
    modelSize = table->model()->rowCount()-1;
    for(quint8 i = 0; i<modelSize; i++)
    {
        indexDest = table->model()->index(modelSize-i,0);
        indexSour = table->model()->index((modelSize-i)-1,0);
        table->model()->setData(indexDest,table->model()->data(indexSour,Qt::DisplayRole),Qt::DisplayRole);
        table->model()->setData(indexDest,table->model()->data(indexSour,Qt::UserRole),Qt::UserRole);
    }
    indexDest = table->model()->index(0, 0);
    table->model()->setData(indexDest, QString("%1").arg(time.currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz")), Qt::DisplayRole);
    table->model()->setData(indexDest, (quint32)buf, Qt::UserRole);
}

void BScanControl::changeRow(QModelIndex index)
{
    qDebug()<<table->model()->data(index,Qt::UserRole);
}

BScanControl::~BScanControl()
{
    delete ui;
}
