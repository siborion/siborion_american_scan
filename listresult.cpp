#include "listresult.h"
#include "ui_listresult.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>

ListResult::ListResult(QWidget *parent, CurParam *link) :
    QDialog(parent),
    ui(new Ui::ListResult)
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
    twListResult  = new adjview(15, lst, columnPercent);
    twListResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    twListResult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->gridLayout->addWidget(twListResult);

    model = (QStandardItemModel*)twListResult->model();
    model->setRowCount(0);

    QString str = QString("SELECT session_time, regim_side, count(*) FROM history  WHERE patient=%1 GROUP BY patient, session_time;").arg(curParam->patientId);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        i = 0;
        while(sql.next())
        {
            twListResult->model()->insertRow(i);
            index = twListResult->model()->index(i, 0);
            twListResult->model()->setData(index, sql.record().value(0).toDateTime(), Qt::DisplayRole);
            index = twListResult->model()->index(i, 1);
            twListResult->model()->setData(index, (sql.record().value(1).toUInt()==0)?"OD":"OS", Qt::DisplayRole);
            index = twListResult->model()->index(i, 2);
            twListResult->model()->setData(index, sql.record().value(2).toString(), Qt::DisplayRole);
            i++;
        }
    }
}

ListResult::~ListResult()
{
    delete ui;
}
