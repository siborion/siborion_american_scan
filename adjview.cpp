#include "adjview.h"

adjview::adjview(QTableView *parent) :
    QTableView(parent)
{
    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 14px;"
                         "font-size: 14px; }";
    horizontalHeader()->setStyleSheet(styleSheet);
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
//    verticalHeader()->setDefaultSectionSize(15);
    setMinimumHeight(rowHeight(0)*row + 4);
    setMaximumHeight(rowHeight(0)*row + 4);
    horizontalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
//    setFrameShape(QFrame::WinPanel);
    setFrameShape(QFrame::Box);

    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    horizontalHeader()->setStyleSheet(styleSheet);
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
    setFrameShape(QFrame::Box);
    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    horizontalHeader()->setStyleSheet(styleSheet);
}


adjview::adjview(QList<int> col, QTableView *parent):
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(col.count());
    setModel(model);
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(col);
    horizontalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
    setFrameShape(QFrame::Box);
    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    horizontalHeader()->setStyleSheet(styleSheet);

}

adjview::adjview(QList<int> col, int row, QTableView *parent):
    QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(col.count());
    model->setRowCount(row);
    setModel(model);
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setColumnPercent(col);
    horizontalHeader()->setSectionsClickable(false);
    setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
    setFrameShape(QFrame::Box);
    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    horizontalHeader()->setStyleSheet(styleSheet);
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
    setFrameShape(QFrame::Box);
    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    horizontalHeader()->setStyleSheet(styleSheet);

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
