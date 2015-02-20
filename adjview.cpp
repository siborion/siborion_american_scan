#include "adjview.h"

adjview::adjview(QTableView *parent) :
    QTableView(parent)
{
}

adjview::adjview(int row, int col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row);
    model->setColumnCount(col);
    setModel(model);
    verticalHeader()->hide();
    horizontalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
    verticalHeader()->setDefaultSectionSize(15);
    setMinimumHeight(rowHeight(0)*row + 4);
    setMaximumHeight(rowHeight(0)*row + 4);
    horizontalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
    setFrameShape(QFrame::WinPanel);
}

adjview::adjview(int row, QStringList col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row);
    model->setColumnCount(col.count());
    setModel(model);
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
    model->setHorizontalHeaderLabels(col);
    verticalHeader()->setDefaultSectionSize(15);
    setMinimumHeight(rowHeight(0)*row + horizontalHeader()->height() + 4);
    setMaximumHeight(rowHeight(0)*row + horizontalHeader()->height() + 4);
    horizontalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
    setFrameShape(QFrame::WinPanel);
}

adjview::adjview(QStringList row, int col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row.count());
    model->setColumnCount(col);
    setModel(model);
    horizontalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
    model->setVerticalHeaderLabels(row);
    verticalHeader()->setDefaultSectionSize(20);
    setMinimumHeight(rowHeight(0)*row.count() + horizontalHeader()->height() + 4);
    setMaximumHeight(rowHeight(0)*row.count() + horizontalHeader()->height() + 4);
    verticalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
    setFrameShape(QFrame::WinPanel);
}

void adjview::setColumnPercent(QList<int> percentList)
{
    quint16 viewWidht;
    quint8 colCount;
    columnPercent = percentList;
    colCount  = columnPercent.count();
    viewWidht = width();
    for(quint8 i=0; i<colCount; i++)
    {
        this->setColumnWidth(i, (viewWidht*columnPercent.at(i))/100);
    }
}

void adjview::resizeEvent( QResizeEvent *__e )
{
    QResizeEvent *tmp; //заглушка
    tmp = __e;
    tmp->size();
    setColumnPercent(columnPercent);
}
