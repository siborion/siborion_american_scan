#include "adjview.h"

adjview::adjview(QTableView *parent) :
    QTableView(parent)
{

}

adjview::adjview(int row, int col, QList<int> columnPercent, QTableView *parent) :
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row);
    model->setColumnCount(col);
    setModel(model);
    verticalHeader()->hide();
    horizontalHeader()->hide();
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
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
