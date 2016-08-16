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
    this->setMaximumWidth(300);
    table = new adjview(il, 80);
    for(quint8 i=0; i<3; i++)
    {
        pbSample.append(new BScanButton());
        ui->layoutGroupBox->addWidget(pbSample.last(),0,i);
    }
    pbSample.last()->setEnabled(false);
    pbUp   = new QPushButton("<<");
    pbDown = new QPushButton(">>");
    ui->layoutGroupBox->addWidget(table,  1, 0, 1, 3);
    ui->layoutGroupBox->addWidget(pbUp,   2, 0);
    ui->layoutGroupBox->addWidget(pbDown, 2, 1);
    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(pbUp,   SIGNAL(clicked()), SLOT(slPbUpClick()));
    connect(pbDown, SIGNAL(clicked()), SLOT(slPbDownClick()));
}

unsigned char *BScanControl::getBuf()
{
    quint8 nomRow;
    quint32 ttt;
    unsigned char *p;
    QModelIndex index;
    nomRow = table->currentIndex().row();
    index = table->model()->index(nomRow,0);
    ttt = table->model()->data(index, Qt::UserRole).toLongLong();
    p = (unsigned char *)ttt;
    return p;
}

void BScanControl::setBuf(unsigned char *buf)
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
    table->model()->setData(indexDest, QString("%1").arg(time.currentDateTime().toString("MM.dd.yyyy hh:mm:ss.zzz")), Qt::DisplayRole);
//!!!!!!!!!!!!!!!!!!!!!!!!!!1
//    table->model()->setData(indexDest, (quint32)buf, Qt::UserRole);
}

void BScanControl::changeRow(QModelIndex index)
{
    QString sTmp;
    sTmp.append(table->model()->data(index, Qt::UserRole+1).toString());
    emit sgUpdateArray  (&sTmp);
    sTmp.clear();
    sTmp.append(table->model()->data(index, Qt::UserRole+2).toString());
    emit sgUpdateArrow  (&sTmp);
    sTmp.clear();
    sTmp.append(table->model()->data(index, Qt::UserRole+3).toString());
    emit sgUpdateCaliper(&sTmp);
}

void BScanControl::changeRowFirst()
{
    QModelIndex index;
    index = table->model()->index(0,0);

    table->setCurrentIndex(index);
    changeRow(index);

}

void BScanControl::slSetArray  (QString *array)
{
    QModelIndex index;
    index = table->currentIndex();
    table->model()->setData(index, *array, Qt::UserRole+1);
}

void BScanControl::slSetArrow  (QString *arrow)
{
    QModelIndex index;
    index = table->currentIndex();
    table->model()->setData(index, *arrow, Qt::UserRole+2);
}

void BScanControl::slSetCaliper(QString *caliper)
{
    QModelIndex index;
    index = table->currentIndex();
    table->model()->setData(index, *caliper, Qt::UserRole+3);
}

void BScanControl::slPbDownClick(void)
{
    QModelIndex index;
    quint8 nomRow;
    nomRow = table->currentIndex().row();
    if(nomRow<(table->model()->rowCount()-1))
        nomRow++;
    index = table->model()->index(nomRow, 0);
    table->setCurrentIndex(index);
}

void BScanControl::slPbUpClick(void)
{
    QModelIndex index;
    quint8 nomRow;
    nomRow = table->currentIndex().row();
    if(nomRow>0)
        nomRow--;
    index = table->model()->index(nomRow, 0);
    table->setCurrentIndex(index);
}

BScanControl::~BScanControl()
{
    delete ui;
}
