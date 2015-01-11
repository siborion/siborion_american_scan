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
    twMeas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(twMeas);

    modelOD = new QStandardItemModel();
    modelOS = new QStandardItemModel();

    modelOD->setHorizontalHeaderLabels(lst);
    modelOS->setHorizontalHeaderLabels(lst);

    twMeas->setModel(modelOD);

    connect(twMeas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRowSlot(QModelIndex)));
}

void sampletable::changeRowSlot(QModelIndex index)
{
    stMeasureParam measureParam;
    QStringList listExtremum;
    index = twMeas->model()->index(index.row(), 0);
    measureParam.Sample = twMeas->model()->data(index, roleSample).toByteArray();
    measureParam.Cornea = twMeas->model()->data(index, roleCornea).toDouble();
    measureParam.L1 =     twMeas->model()->data(index, roleL1).toDouble();
    measureParam.L2 =     twMeas->model()->data(index, roleL2).toDouble();
    measureParam.Retina = twMeas->model()->data(index, roleRetina).toDouble();
    listExtremum =        twMeas->model()->data(index, roleExtremum).toStringList();

    index = twMeas->model()->index(index.row(), 1);
    measureParam.ALave = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
    index = twMeas->model()->index(index.row(), 2);
    measureParam.AL    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
    index = twMeas->model()->index(index.row(), 3);
    measureParam.ACD   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
    index = twMeas->model()->index(index.row(), 4);
    measureParam.LT    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
    index = twMeas->model()->index(index.row(), 5);
    measureParam.VIT   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
    foreach (QString val, listExtremum)
    {
        measureParam.extremum.append(val.toUInt());
    }
    emit changeRow(&measureParam);
}

void sampletable::addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam* measureParam)
{
    QModelIndex index;
    quint8 rowNom;
    QStringList listExtremum;
    foreach (quint16 val, *extremum)
    {
        listExtremum.append(QString("%1").arg(val));
    }
    rowNom = twMeas->model()->rowCount();
    twMeas->model()->insertRow(rowNom);
    index = twMeas->model()->index(rowNom, 0);
    twMeas->model()->setData(index, rowNom+1,     Qt::DisplayRole);
    twMeas->model()->setData(index, *Sample,      roleSample);
    twMeas->model()->setData(index, listExtremum, roleExtremum);
    editSample(rowNom, measureParam);
}

void sampletable::editSample(quint16 rowNom, stMeasureParam* measureParam)
{
    QModelIndex index;
    index = twMeas->model()->index(rowNom, 0);
    twMeas->model()->setData(index, measureParam->Cornea, roleCornea);
    twMeas->model()->setData(index, measureParam->L1,     roleL1);
    twMeas->model()->setData(index, measureParam->L2,     roleL2);
    twMeas->model()->setData(index, measureParam->Retina, roleRetina);

    index = twMeas->model()->index(rowNom, 1);
    twMeas->model()->setData(index, measureParam->ALave, Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 2);
    twMeas->model()->setData(index, measureParam->AL, Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 3);
    twMeas->model()->setData(index, measureParam->ACD, Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 4);
    twMeas->model()->setData(index, measureParam->LT, Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 5);
    twMeas->model()->setData(index, measureParam->VIT, Qt::DisplayRole);
}

void sampletable::editSample(stMeasureParam* measureParam)
{
    quint8 rowNom;
    rowNom = twMeas->currentIndex().row();
    editSample(rowNom, measureParam);
}
