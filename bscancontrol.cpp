#include "bscancontrol.h"
#include "ui_bscancontrol.h"
#include <QDateTime>
#include <QDebug>
#include "blistresult.h"
#include <QSqlQuery>
#include <QSqlRecord>


BScanControl::BScanControl(QWidget *parent, CurParam *link) :
    QWidget(parent),
    ui(new Ui::BScanControl)
{
    curParam = link;
    QStringList sl;
    QList<int>  il;
    sl << " ";
    il << 100;
    ui->setupUi(this);
    this->setMaximumWidth(190);
    numTab = -1;

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

    connect(table0->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow0(QModelIndex)));
    connect(table1->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow1(QModelIndex)));
    connect(table2->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow2(QModelIndex)));
    connect(pbUp,   SIGNAL(clicked()), SLOT(slPbUpClick()));
    connect(pbDown, SIGNAL(clicked()), SLOT(slPbDownClick()));

    connect(pbSave, SIGNAL(clicked(bool)), SLOT(slSave()));
    connect(pbLoad, SIGNAL(clicked(bool)), SLOT(slLoad()));

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
//    qDebug()<<"ttt"<<ttt;
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
    qDebug()<<buf;
    table->model()->setData(indexDest, (quint32)buf, Qt::UserRole);
}

void BScanControl::changeRow0(QModelIndex index)
{
    table=table0;
    changeRow(index);
}

void BScanControl::changeRow1(QModelIndex index)
{
    table=table1;
    changeRow(index);
}

void BScanControl::changeRow2(QModelIndex index)
{
    table=table2;
    changeRow(index);
}

void BScanControl::changeRow(QModelIndex index)
{
    qDebug()<<table->model()->data(index, Qt::DisplayRole).toString();

    QString sTmp;
    sTmp.append(table->model()->data(index, Qt::UserRole+1).toString());
    emit sgUpdateArray  (&sTmp);
    sTmp.clear();
    sTmp.append(table->model()->data(index, Qt::UserRole+2).toString());
    emit sgUpdateArrow  (&sTmp);
    sTmp.clear();
    sTmp.append(table->model()->data(index, Qt::UserRole+3).toString());
    emit sgUpdateCaliper(&sTmp);
    sTmp.clear();
    sTmp.append(table->model()->data(index, Qt::UserRole+4).toString());
    emit sgUpdateText(&sTmp);
    //    qDebug()<<sTmp;

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

void BScanControl::slSetText(QString *text)
{
    QModelIndex index;
    index = table->currentIndex();
    table->model()->setData(index, *text, Qt::UserRole+4);
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

void BScanControl::clearDraw()
{
    QModelIndex index;
    index = table->model()->index(table->currentIndex().row(),0);
    table->model()->setData(index,"",Qt::UserRole+1);
    table->model()->setData(index,"",Qt::UserRole+2);
    table->model()->setData(index,"",Qt::UserRole+3);
    table->model()->setData(index,"",Qt::UserRole+4);
}

quint8 BScanControl::start(void)
{
    numTab++;
    if(numTab>2)
        numTab = 0;
    if(numTab==2)
    {
        table = table2;
        tab->setCurrentIndex(2);
    }
    else
    {
        if(numTab==1)
        {
            table = table1;
            tab->setCurrentIndex(1);
        }
        else
        {
            table = table0;
            tab->setCurrentIndex(0);
        }
    }


    QModelIndex index;
    quint8 modelSize;
    modelSize = table->model()->rowCount()-1;
    for(quint8 i = 0; i<modelSize; i++)
    {
        index = table->model()->index(i,0);
        table->model()->setData(index,"",Qt::DisplayRole);
    }

    return numTab;
}

quint8 BScanControl::getCurTable()
{
    return (tab->currentIndex());
}

void BScanControl::slSave()
{
    QStandardItemModel *tb0, *tb1, *tb2;
    tb0 = (QStandardItemModel*)table0->model();
    tb1 = (QStandardItemModel*)table1->model();
    tb2 = (QStandardItemModel*)table2->model();
    emit sgSave(tb0, tb1, tb2);
}

void BScanControl::slLoad()
{
    QByteArray sample;
    quint32 *pointer;
    quint32 uuu;
    quint8 i[3];
    quint16 j;

    QDateTime selectTime;
    QSqlQuery query;
    QModelIndex index;
    BListResult *listResult = new BListResult(this, curParam);
    j = i[0] = i[1] = i[2] = 0;
    if(listResult->exec() == QDialog::Accepted)
    {
        index = listResult->twBListResult->currentIndex();
        index = listResult->twBListResult->model()->index(index.row(), 0);
        selectTime = listResult->twBListResult->model()->data(index, Qt::DisplayRole).toDateTime();
        QString str = "SELECT time, samples, samples_0, samples_1, samples_2, samples_3, samples_4, tab FROM history_bscan  WHERE patient=:patient AND session_time=:session_time;";
        query.prepare(str);
        query.bindValue(":patient", curParam->patientId);
        query.bindValue(":session_time", selectTime);


        if(query.exec())
        {
            quint8 tab;
            while(query.next())
            {
                pointer = &uuu;

                tab = query.value(query.record().indexOf("tab")).toUInt();

                switch (tab) {
                case 0: table = table0; break;
                case 1: table = table1; break;
                case 2: table = table2; break;
                }
                index = table->model()->index(i[tab], 0);
                table->model()->setData(index, query.value(query.record().indexOf("time")).toString(), Qt::DisplayRole);
                table->model()->setData(index, query.value(query.record().indexOf("samples_1")).toString(), Qt::UserRole+1);
                table->model()->setData(index, query.value(query.record().indexOf("samples_2")).toString(), Qt::UserRole+2);
                table->model()->setData(index, query.value(query.record().indexOf("samples_3")).toString(), Qt::UserRole+3);
                table->model()->setData(index, query.value(query.record().indexOf("samples_4")).toString(), Qt::UserRole+4);
                qDebug()<<tab<<i[tab];
                sample = query.value(query.record().indexOf("samples")).toByteArray();
                sample = qUncompress(sample);
                emit sgSetSample(tab, i[tab], &sample);
                table->model()->setData(index, (quint32)massive+(408000*i[tab])+(408000*80*tab), Qt::UserRole);
                i[tab]++;
                j++;
            }
        }
    }
}

void BScanControl::setMassive(unsigned char* val)
{
    massive = val;
    qDebug()<<"***massive"<<(massive);
//    qDebug()<<"(quint32)&massive[0][0][0]"<<(quint32)(*massive)[0][0][0];
//    qDebug()<<"(quint32)&massive[0][0][0]"<<(quint32)(*massive)[0][1][0];
}

BScanControl::~BScanControl()
{
    delete ui;
}
