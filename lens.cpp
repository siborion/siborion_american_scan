#include "lens.h"

lens::lens(QWidget *parent) :
    QDialog(parent)
{
    QList<int> columnPercent;
    QGridLayout *layout        = new QGridLayout(this);
//----------------------------------------------------------------
    modelLens = new QStandardItemModel();
    modelLens->setRowCount(17);
    modelLens->setColumnCount(2);
    twLens = new adjview();
    twLens->setModel(modelLens);
    twLens->verticalHeader()->hide();
    twLens->horizontalHeader()->hide();

    twLens->setMaximumHeight(520);
    twLens->setMinimumHeight(520);

    twLens->setFrameShape(QFrame::NoFrame);
    twLens->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twLens->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<50<<50;
    twLens->setColumnPercent(columnPercent);

//    modelLens->item(1,1)->setText("asdfasdf");
    modelLens->setItem(1, 1, new QStandardItem("khbkh"));

    twLens->setStyleSheet("QTableView { border: none;"
                                         "background-color: #FFDE21;"
                                         "selection-background-color: #109}");

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    QPushButton *pbOk = new QPushButton(tr("Ok"));

    layout->addWidget(twLens, 0, 0, 1, 2);

    layout->addWidget(pbCancel, 1, 0);
    layout->addWidget(pbOk,     1, 1);
}
