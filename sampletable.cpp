#include "sampletable.h"
#include <QtCore/qmath.h>

sampletable::sampletable(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;

    QVBoxLayout *layout              = new QVBoxLayout(this);

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<23            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
//    twMeas->setMaximumWidth(350);
//    twMeas->setMinimumWidth(280);
//    twMeas->setMaximumHeight(16777215);
//    twMeas->setMinimumHeight(0);
    twMeas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(twMeas);

    modelOD = new QStandardItemModel();
    modelOS = new QStandardItemModel();

    modelOD->setHorizontalHeaderLabels(lst);
    modelOS->setHorizontalHeaderLabels(lst);

    twMeas->setModel(modelOD);

    connect(twMeas, SIGNAL(clicked(QModelIndex)),   SLOT(changeRow(QModelIndex)));
    connect(twMeas, SIGNAL(activated(QModelIndex)), SLOT(changeRow(QModelIndex)));
//    connect(curentParam, SIGNAL(changeSideSignal()), SLOT(changeSide()));
//    connect(curentParam, SIGNAL(changePatientSignal()), SLOT(clearModel()));
    connect(twMeas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex)));
}

void sampletable::changeRow(QModelIndex index)
{
    Q_UNUSED(index);
}
