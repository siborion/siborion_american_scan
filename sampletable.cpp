#include "sampletable.h"
#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>
//#include <QSound>
#include <QThread>
#include <QApplication>


sampletable::sampletable(QWidget *parent, CurParam *link) :
    QFrame(parent)
{
    curParam = link;
    setFrameShape(QFrame::WinPanel);
    setFrameShadow(QFrame::Raised);
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
//    twMeas->setFrameStyle(QFrame::Box);
//    twMeas->setSelectionMode(MultiSelection);
//    twMeas->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
//    twMeas->selectedIndexes();//

//    bells = new QSound(":/test/sinus");

    connect(twMeas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRowSlot(QModelIndex)));
    connect(pbSave,SIGNAL(pressed()),SLOT(saveSlot()));
    connect(pbLoad,SIGNAL(pressed()),SLOT(loadSlot()));
    connect(pbClear,SIGNAL(pressed()),SLOT(del()));
}

void sampletable::saveSlot()
{
    emit save(modelOD, modelOS);
    pbSave->setEnabled(false);
}

void sampletable::loadSlot()
{
    printf("%c", 7);
    QDateTime selectTime;
    QSqlQuery query;
    QModelIndex index;
//    quint16 i=0;
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
                measureParam.LT  = query.value(query.record().indexOf("lt")).toDouble();
                measureParam.ALave  = query.value(query.record().indexOf("al_ave")).toDouble();
                measureParam.Cornea = query.value(query.record().indexOf("cornea")).toUInt();
                measureParam.L1 = query.value(query.record().indexOf("l1")).toUInt();
                measureParam.L2 = query.value(query.record().indexOf("l2")).toUInt();
                measureParam.Retina = query.value(query.record().indexOf("retina")).toUInt();
                Sample = query.value(query.record().indexOf("sample")).toByteArray();
                measureParam.VIT = query.value(query.record().indexOf("vit")).toDouble();
//                curParam->regimSide = (REGIM::RegimSide)query.value(query.record().indexOf("regim_side")).toUInt();
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

    qDebug()<<"measureParam.Sample"<<measureParam.Sample.count();

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
            {
                emit stopMeasure();
                if(twMeas->model()->rowCount()>0)
                    twMeas->selectRow(twMeas->model()->rowCount()-1);
            }
        }
        if (curParam->regimMeasure  == REGIM::AUTO)
        {
            emit stopMeasure();
            if(twMeas->model()->rowCount()>0)
                twMeas->selectRow(twMeas->model()->rowCount()-1);
        }
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
    twMeas->model()->setData(index, QString("%1").arg(measureParam->ALave, 4, 'f', 2, '0'), Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 2);
    twMeas->model()->setData(index, QString("%1").arg(measureParam->AL,    4, 'f', 2, '0'), Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 3);
    twMeas->model()->setData(index, QString("%1").arg(measureParam->ACD,   4, 'f', 2, '0'), Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 4);
    twMeas->model()->setData(index, QString("%1").arg(measureParam->LT,    4, 'f', 2, '0'), Qt::DisplayRole);
    index = twMeas->model()->index(rowNom, 5);
    twMeas->model()->setData(index, QString("%1").arg(measureParam->VIT,   4, 'f', 2, '0'), Qt::DisplayRole);
    calculateAvg();
//    bells->play();
//    qDebug()<<"QSOUND";
    QApplication::beep();
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
    averageParam.ACD    = averageParam.ALave    = averageParam.LT    = averageParam.VIT    = 0;
    averageParam.ACDdiv = averageParam.ALavediv = averageParam.LTdiv = averageParam.VITdiv = 0;
    ALave = ACDave = LTave = VITave = 0;
    rowCount = twMeas->model()->rowCount();
    if(rowCount==0)
    {
        averageParam.ACD=0;
        averageParam.ACDdiv=0;
        averageParam.ALave=0;
        averageParam.ALavediv=0;
        averageParam.LT=0;
        averageParam.LTdiv=0;
        averageParam.VIT=0;
        averageParam.VITdiv=0;
        emit sendAvg(&averageParam);
        return;
    }

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i, 1);
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
        index = twMeas->model()->index(i, 1);
        AL    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 3);
        ACD   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 4);
        LT    = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        index = twMeas->model()->index(i, 5);
        VIT   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();

        averageParam.ALavediv  += pow((AL  - ALave), 2);
        averageParam.ACDdiv += pow((ACD - ACDave),2);
        averageParam.LTdiv  += pow((LT  - LTave), 2);
        averageParam.VITdiv += pow((VIT - VITave),2);

        AL  = pow(AL,2);
        ACD = pow(ACD,2);
        LT  = pow(LT,2);
        VIT = pow(VIT,2);

        averageParam.ACD += ACD;
        averageParam.ALave  += AL;
        averageParam.LT  += LT;
        averageParam.VIT += VIT;
    }

    averageParam.ACD /= rowCount;
    averageParam.ALave  /= rowCount;
    averageParam.LT  /= rowCount;
    averageParam.VIT /= rowCount;

    averageParam.ALavediv  /= rowCount;
    averageParam.ACDdiv /= rowCount;
    averageParam.LTdiv  /= rowCount;
    averageParam.VITdiv /= rowCount;

    averageParam.ACD = pow(averageParam.ACD, 0.5);
    averageParam.ALave  = pow(averageParam.ALave,  0.5);
    averageParam.LT  = pow(averageParam.LT,  0.5);
    averageParam.VIT = pow(averageParam.VIT, 0.5);

    averageParam.ACDdiv = pow(averageParam.ACDdiv, 0.5);
    averageParam.ALavediv  = pow(averageParam.ALavediv,  0.5);
    averageParam.LTdiv  = pow(averageParam.LTdiv,  0.5);
    averageParam.VITdiv = pow(averageParam.VITdiv, 0.5);

    averageParam.ACD = round(averageParam.ACD*100)/100;
    averageParam.ALave  = round(averageParam.ALave*100) /100;
    averageParam.LT  = round(averageParam.LT*100) /100;
    averageParam.VIT = round(averageParam.VIT*100)/100;

    averageParam.ACDdiv = round(averageParam.ACDdiv*100)/100;
    averageParam.ALavediv  = round(averageParam.ALavediv*100) /100;
    averageParam.LTdiv  = round(averageParam.LTdiv*100) /100;
    averageParam.VITdiv = round(averageParam.VITdiv*100)/100;

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i, 1);
        curDev = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
        curDev = round(abs(averageParam.ALave*100 - curDev*100));
        curDev /= 100;
        for(int j=0; j<=5; j++)
        {
            color.setNamedColor(curDev>=0.2?"yellow":"white");
            twMeas->model()->setData(twMeas->model()->index(i, j), color, Qt::BackgroundRole);
        }
    }

    if(curParam->regimMeasure == REGIM::MANUAL)
        averageParam.ACD = 0;

    curParam->ACD = averageParam.ACD;
    curParam->ALave = averageParam.ALave;
    emit sendAvg(&averageParam);
}

void sampletable::changeRegimManual(QString objectName)
{
    qDebug()<<objectName;
    bool bAuto, bCataract;
    QMessageBox msg;
    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twMeas->model();

    if(model->rowCount()>0)
    {
        msg.setInformativeText("Do you want to save your changes?");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msg.setDefaultButton(QMessageBox::Save);

        if(((objectName=="OS")&&(curParam->regimSide==REGIM::OD))||((objectName=="OD")&&(curParam->regimSide==REGIM::OS)))
        {
            if(pbSave->isEnabled()&&(QMessageBox::Save == msg.exec()))
                saveSlot();
        }

        if(((objectName=="rbAutoFreeze")||(objectName=="rbAuto"))&&(curParam->regimSide==REGIM::MANUAL))
        {
            if(pbSave->isEnabled()&&(QMessageBox::Save == msg.exec()))
                saveSlot();
        }

        if((objectName=="rbManual")&&((curParam->regimSide==REGIM::AUTOFREEZ)||(curParam->regimSide==REGIM::AUTO)))
        {
            if(pbSave->isEnabled()&&(QMessageBox::Save == msg.exec()))
                saveSlot();
        }
    }

    if(QObject::sender())
    {
        qDebug()<<QObject::sender()->objectName();
        qDebug()<<"test";
    }

    if (!((objectName=="rbOD")||(objectName=="rbOS")))
        clearAll();

    bCataract = (curParam->regimCataract == REGIM::CATARACT);
    bAuto = (curParam->regimMeasure != REGIM::MANUAL);

    if (objectName=="rbCataract")
        bCataract = true;

    if (objectName=="Aphakic")
        bCataract = false;

    if (objectName=="rbManual")
        bAuto = false;

    if ((objectName=="rbAuto")||(objectName=="rbAutoFreeze"))
        bAuto = true;

    if(bAuto)
    {
        if(bCataract)
        {
            columnPercent<<10      <<23            <<15      <<15       <<15      <<15;
            lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
        }
        else
        {
            columnPercent<<10      <<83            <<0      <<0       <<0      <<0;
            lst          <<tr("No")<<tr("AveVelAl");
        }
    }
    else
    {
        columnPercent<<10      <<83            <<0      <<0       <<0      <<0;
        lst          <<tr("No")<<tr("Distance");
    }

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
    qDebug()<<"ClearAll";
    QStandardItemModel *model;
    model = (QStandardItemModel*)twMeas->model();
    model->setRowCount(0);
    emit clearAllSignal();
}

void sampletable::del()
{
    QApplication::beep();

    QModelIndexList indexes = twMeas->selectionModel()->selectedRows();

    if (!indexes.count())
        return;

    if (QMessageBox::question(this, tr("Removing data"), tr("Data will be removed. Continue?"),
                              QMessageBox::Yes, QMessageBox::No ) == QMessageBox::No)
        return;

    int removed = 0;
    int count = 1;
    int start = indexes[0].row();

    for (int i = 1; i < indexes.count(); ++i) {
        if (indexes.at(i - 1).row() != indexes.at(i).row() - 1) {
            twMeas->model()->removeRows(start - removed, count);
            removed += count;
            start = indexes.at(i).row();
            count = 1;
        } else {
            ++count;
        }
    }
    twMeas->model()->removeRows(start - removed, count);
    calculateAvg();
    emit changeGlas();
}

void sampletable::keyPressEvent(QKeyEvent * keyEvent)
{
    if(keyEvent->key() == Qt::Key_Delete)
    {
        twMeas->model()->removeRow(twMeas->currentIndex().row());
        calculateAvg();
        emit changeGlas();
    }
}

void sampletable::changeGlasSlot()
{
    QModelIndex index;
    if(curParam->regimSide==0)
    {
        if(twMeas->model()==modelOD)
            return;
        twMeas->setModel(modelOD);
    }
    else
    {
        if(twMeas->model()==modelOS)
            return;
        twMeas->setModel(modelOS);
    }
    connect(twMeas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRowSlot(QModelIndex)));

    calculateAvg();
    if(twMeas->model()->rowCount()>0)
    {
        twMeas->selectRow(twMeas->model()->rowCount()-1);
        index=twMeas->model()->index(twMeas->model()->rowCount()-1,0);
        changeRowSlot(index);
    }
    else
        emit clearSample();
}
