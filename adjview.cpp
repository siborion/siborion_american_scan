#include "adjview.h"

adjview::adjview(QTableView *parent) :
    QTableView(parent)
{
//    QPalette palette;
//    QBrush brush(QColor(    Qt::gray));
//    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Base, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//    QBrush brush1(QColor(    Qt::gray));
//    brush1.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//    setPalette(palette);
//    horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:gray}");
}

adjview::adjview(int row, int col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
//    QPalette palette;
//    QBrush brush(QColor(    Qt::gray));
//    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Base, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//    QBrush brush1(QColor(    Qt::gray));
//    brush1.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//    setPalette(palette);

    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row);
    model->setColumnCount(col);
    setModel(model);
    verticalHeader()->hide();
    horizontalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
//    horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:gray}");
    verticalHeader()->setDefaultSectionSize(15);
    setMinimumHeight(rowHeight(0)*row + 2);
    setMaximumHeight(rowHeight(0)*row + 2);
    horizontalHeader()->setSectionsClickable(false);
}

adjview::adjview(int row, QStringList col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
//    QPalette palette;
//    QBrush brush(QColor(    Qt::gray));
//    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Base, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//    QBrush brush1(QColor(    Qt::gray));
//    brush1.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//    setPalette(palette);

    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row);
    model->setColumnCount(col.count());
    setModel(model);
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
    model->setHorizontalHeaderLabels(col);
//    horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:gray}");
    verticalHeader()->setDefaultSectionSize(15);
    setMinimumHeight(rowHeight(0)*row + horizontalHeader()->height() + 2);
    setMaximumHeight(rowHeight(0)*row + horizontalHeader()->height() + 2);
    horizontalHeader()->setSectionsClickable(false);
}

adjview::adjview(QStringList row, int col, QList<int> columnPercent, QTableView *parent):
    QTableView(parent)
{
//    QPalette palette;
//    QBrush brush(QColor(    Qt::gray));
//    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Base, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//    QBrush brush1(QColor(    Qt::gray));
//    brush1.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//    setPalette(palette);

    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(row.count());
    model->setColumnCount(col);
    setModel(model);
    horizontalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(columnPercent);
    model->setVerticalHeaderLabels(row);
//    verticalHeader()->setStyleSheet("QHeaderView::section{background-color:gray}");
    verticalHeader()->setDefaultSectionSize(20);
    setMinimumHeight(rowHeight(0)*row.count() + horizontalHeader()->height() + 2);
    setMaximumHeight(rowHeight(0)*row.count() + horizontalHeader()->height() + 2);
    verticalHeader()->setSectionsClickable(false);
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
