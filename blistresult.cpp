#include "blistresult.h"
#include "ui_blistresult.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>

BListResult::BListResult(QWidget *parent, CurParam *link) :
    QDialog(parent),
    ui(new Ui::BListResult)
{
    QStandardItemModel *model;
    QModelIndex index;
    quint16 i;

    ui->setupUi(this);

    curParam = link;

    QList<int> columnPercent;
    QStringList lst;

    lst.clear();
    columnPercent.clear();
    columnPercent<<50        <<25        <<25;
    lst          <<tr("Data")<<tr("Side")<<tr("No of scan");
    twBListResult  = new adjview(15, lst, columnPercent);
    twBListResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    twBListResult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->gridLayout->addWidget(twBListResult);

    model = (QStandardItemModel*)twBListResult->model();
    model->setRowCount(0);

    QString str = QString("SELECT session_time, session, count(*) FROM history_bscan  WHERE patient=%1 GROUP BY patient, session_time, session;").arg(curParam->patientId);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        i = 0;
        while(sql.next())
        {
            twBListResult->model()->insertRow(i);
            index = twBListResult->model()->index(i, 0);
            twBListResult->model()->setData(index, sql.record().value(0).toDateTime(), Qt::DisplayRole);
            index = twBListResult->model()->index(i, 1);
//            twBListResult->model()->setData(index, (sql.record().value(1).toUInt()==0)?"OD":"OS", Qt::DisplayRole);
            twBListResult->model()->setData(index, sql.record().value(1).toUInt(), Qt::DisplayRole);
            index = twBListResult->model()->index(i, 2);
            twBListResult->model()->setData(index, sql.record().value(2).toUInt(), Qt::DisplayRole);
            i++;
        }
    }
}

BListResult::~BListResult()
{
    delete ui;
}
