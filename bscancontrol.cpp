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
    this->setMaximumWidth(190);

    table0 = new adjview(il, 80);
    table0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table0->verticalHeader()->setDefaultSectionSize(12);

    table1 = new adjview(il, 80);
    table1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table1->verticalHeader()->setDefaultSectionSize(12);

    table2 = new adjview(il, 80);
    table2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table2->verticalHeader()->setDefaultSectionSize(12);

    table = table0;

    tab = new QTabWidget();
    tab->addTab(table0, "1");
    tab->addTab(table1, "2");
    tab->addTab(table2, "3");

//    pbSample.last()->setEnabled(false);

    pbUp   = new QPushButton("<<");
    pbUp->setMaximumWidth(50);
    pbDown = new QPushButton(">>");
    pbDown->setMaximumWidth(50);

    pbLoad = new QPushButton("Load");
    pbSave = new QPushButton("Save");

    ui->layoutGroupBox->addWidget(tab  ,  3, 0, 1, 2);
    ui->layoutGroupBox->addWidget(pbUp,   4, 0, 1, 2);
    ui->layoutGroupBox->addWidget(pbDown, 4, 1, 1, 1);

    ui->layoutGroupBox->addWidget(pbLoad, 5, 0, 1, 2);
    ui->layoutGroupBox->addWidget(pbSave, 6, 0, 1, 2);

    connect(table0->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(table1->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(table2->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));
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
    table->model()->setData(indexDest, (quint32)buf, Qt::UserRole);
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
