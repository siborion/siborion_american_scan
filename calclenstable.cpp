#include "calclenstable.h"
#include "ui_calclenstable.h"
#include <QDebug>


CalcLensTable::CalcLensTable(adjview * parent) :
    adjview(parent)
{
//    ui->setupUi(this);
//    this->row
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    this->setFrameShape(QFrame::Panel);
    this->setFrameShadow(QFrame::Plain);
    this->setStyleSheet(QStringLiteral("gridline-color: rgb(10, 10, 17);"));

}

CalcLensTable::CalcLensTable(int row, int col, QList<int> pr, QTableView *parent):
    adjview(row, col, pr, parent)
{
    QModelIndex index;
    tableModel = this->model();

//    model = this->selectionModel();

    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Plain);
    this->setStyleSheet(QStringLiteral("gridline-color: rgb(200, 200, 255);"));
    this->setSpan(0,0,3,1);
    this->setSpan(3,0,7,1);
    this->setSpan(0,1,1,2);
    this->setSpan(1,1,1,2);
    this->setSpan(0,3,1,2);
    this->setSpan(1,3,1,2);
    this->setSpan(0,5,1,2);
    this->setSpan(1,5,1,2);


    index = this->tableModel->index(1,1);
    tableModel->setData(index, "666", Qt::DisplayRole);
    tableModel->setData(index, QColor(10,10,10,10),Qt::BackgroundColorRole);

    this->verticalHeader()->setDefaultSectionSize(16);

}


CalcLensTable::~CalcLensTable()
{
    delete ui;
}
