#include "sampletable.h"
#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>

sampletable::sampletable(QWidget *parent, CurParam *link) :
    QWidget(parent)
{
    curParam = link;

    QList<int> columnPercent;
    QStringList lst;

    QGridLayout *layout              = new QGridLayout(this);

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<23            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
    twMeas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    pbSave = new QPushButton("Save");
    pbLoad = new QPushButton("Load");
    pbClear  = new QPushButton("Clear");

    pbSave->setEnabled(false);

    layout->addWidget(twMeas,0,0,1,3);
    layout->addWidget(pbSave,1,0);
    layout->addWidget(pbLoad,1,1);
    layout->addWidget(pbClear, 1,2);

    modelOD = new QStandardItemModel();
    modelOS = new QStandardItemModel();

    modelOD->setHorizontalHeaderLabels(lst);
    modelOS->setHorizontalHeaderLabels(lst);

    twMeas->setModel(modelOD);

    connect(twMeas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRowSlot(QModelIndex)));
    connect(pbSave,SIGNAL(pressed()),SLOT(saveSlot()));
    connect(pbLoad,SIGNAL(pressed()),SLOT(loadSlot()));
    connect(pbClear,SIGNAL(pressed()),SLOT(clearAll()));
}

void sampletable::saveSlot()
{
    emit save(modelOD, modelOS);
    pbSave->setEnabled(false);
}

void sampletable::loadSlot()
{
    QDateTime selectTime;
    QSqlQuery query;
    QModelIndex index;
    quint16 i=0;
    stMeasureParam measureParam;
    QByteArray Sample;
    QList<quint16> extremum;
    ListResult *listResult = new ListResult(this, curParam);
    if(listResult->exec() == QDialog::Accepted)
    {
        if(listResult->twListResult->currentIndex().row()>=0)
        {
            index = listResult->twListResult->currentIndex();
            index = listResult->twListResult->model()->index(index.row(), 0);
            selectTime = listResult->twListResult->model()->data(index, Qt::DisplayRole).toDateTime();
            QString str = "SELECT * FROM history  WHERE patient=:patient AND session_time=:session_time;";
            query.prepare(str);
            query.bindValue(":patient", curParam->patientId);
            query.bindValue(":session_time", selectTime);

            clearAll();
            pbSave->setEnabled(false);

            if(query.exec())
            {
                while(query.next())
                {
                measureParam.ACD = query.value(query.record().indexOf("acd")).toDouble();
                measureParam.AL  = query.value(query.record().indexOf("al")).toDouble();
                measureParam.ALave  = query.value(query.record().indexOf("al_ave")).toDouble();
                measureParam.Cornea = query.value(query.record().indexOf("cornea")).toUInt();
                measureParam.L1 = query.value(query.record().indexOf("l1")).toUInt();
                measureParam.L2 = query.value(query.record().indexOf("l2")).toUInt();
                measureParam.Retina = query.value(query.record().indexOf("retina")).toUInt();
                Sample = query.value(query.record().indexOf("sample")).toByteArray();
                measureParam.VIT = query.value(query.record().indexOf("vit")).toDouble();
                curParam->regimSide = (REGIM::RegimSide)query.value(query.record().indexOf("regim_side")).toUInt();
                addSample(&Sample, &extremum, &measureParam, true);
                }
            }
            emit changeGlas();
        }
    }
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

void sampletable::addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam* measureParam, bool fromBase)
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
    if(!fromBase)
    {
        if (curParam->regimMeasure  == REGIM::AUTOFREEZ)
        {
            if(twMeas->model()->rowCount()>=10)
                emit stopMeasure();
        }
        if (curParam->regimMeasure  == REGIM::AUTO)
            emit stopMeasure();
        pbSave->setEnabled(true);
    }
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
    calculateAvg();
}

void sampletable::editSample(stMeasureParam* measureParam)
{
    quint8 rowNom;
    rowNom = twMeas->currentIndex().row();
    editSample(rowNom, measureParam);
}

void sampletable::calculateAvg()
{
    QColor color;
    double AL, ACD, LT, VIT;
    double ALave, ACDave, LTave, VITave; //среднее
    double curDev;
    QModelIndex index;
    quint8 rowCount;
    stAverageParam averageParam;
    averageParam.ACD    = averageParam.AL    = averageParam.LT    = averageParam.VIT    = 0;
    averageParam.ACDdiv = averageParam.ALdiv = averageParam.LTdiv = averageParam.VITdiv = 0;
    ALave = ACDave = LTave = VITave = 0;
    rowCount = twMeas->model()->rowCount();

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i, 2);
        AL    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 3);
        ACD   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 4);
        LT    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 5);
        VIT   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        ALave += AL; ACDave += ACD; LTave += LT; VITave += VIT;
    }
    ACDave /= rowCount;
    ALave  /= rowCount;
    LTave  /= rowCount;
    VITave /= rowCount;

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i, 2);
        AL    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 3);
        ACD   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 4);
        LT    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 5);
        VIT   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();

        averageParam.ALdiv  += pow((AL  - ALave), 2);
        averageParam.ACDdiv += pow((ACD - ACDave),2);
        averageParam.LTdiv  += pow((LT  - LTave), 2);
        averageParam.VITdiv += pow((VIT - VITave),2);

        AL  = pow(AL,2);
        ACD = pow(ACD,2);
        LT  = pow(LT,2);
        VIT = pow(VIT,2);

        averageParam.ACD += ACD;
        averageParam.AL  += AL;
        averageParam.LT  += LT;
        averageParam.VIT += VIT;
    }

    averageParam.ACD /= rowCount;
    averageParam.AL  /= rowCount;
    averageParam.LT  /= rowCount;
    averageParam.VIT /= rowCount;

    averageParam.ALdiv  /= rowCount;
    averageParam.ACDdiv /= rowCount;
    averageParam.LTdiv  /= rowCount;
    averageParam.VITdiv /= rowCount;

    averageParam.ACD = pow(averageParam.ACD, 0.5);
    averageParam.AL  = pow(averageParam.AL,  0.5);
    averageParam.LT  = pow(averageParam.LT,  0.5);
    averageParam.VIT = pow(averageParam.VIT, 0.5);

    averageParam.ACDdiv = pow(averageParam.ACDdiv, 0.5);
    averageParam.ALdiv  = pow(averageParam.ALdiv,  0.5);
    averageParam.LTdiv  = pow(averageParam.LTdiv,  0.5);
    averageParam.VITdiv = pow(averageParam.VITdiv, 0.5);


    averageParam.ACD = round(averageParam.ACD*100)/100;
    averageParam.AL  = round(averageParam.AL*100) /100;
    averageParam.LT  = round(averageParam.LT*100) /100;
    averageParam.VIT = round(averageParam.VIT*100)/100;

    averageParam.ACDdiv = round(averageParam.ACDdiv*100)/100;
    averageParam.ALdiv  = round(averageParam.ALdiv*100) /100;
    averageParam.LTdiv  = round(averageParam.LTdiv*100) /100;
    averageParam.VITdiv = round(averageParam.VITdiv*100)/100;

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i, 2);
        curDev = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        curDev = round(abs(averageParam.AL*100 - curDev*100));
        curDev /= 100;
        for(int j=0; j<=5; j++)
        {
            color.setNamedColor(curDev>=0.2?"yellow":"white");
            twMeas->model()->setData(twMeas->model()->index(i, j), color, Qt::BackgroundRole);
        }
    }

    curParam->ACD = averageParam.ACD;
    curParam->AL = averageParam.AL;

    emit sendAvg(&averageParam);
}


void sampletable::changeRegimManual()
{
    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model = new QStandardItemModel();

    if (curParam->regimMeasure  == REGIM::MANUAL)
    {
        columnPercent<<10      <<0            <<90      <<0       <<0      <<0;
        lst          <<tr("No")<<tr("AveVelAl")<<tr("Distance");
    }
    else
    {
        columnPercent<<10      <<23            <<15      <<15       <<15      <<15;
        lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    }
    model = (QStandardItemModel*)twMeas->model();
    model->setHorizontalHeaderLabels(lst);
    twMeas->setColumnPercent(columnPercent);
}

void sampletable::startMeasure()
{
    if (curParam->regimMeasure  == REGIM::AUTOFREEZ)
        clearAll();
}

void sampletable::clearAll()
{
    QStandardItemModel *model;
    model = (QStandardItemModel*)twMeas->model();
    model->setRowCount(0);
}

