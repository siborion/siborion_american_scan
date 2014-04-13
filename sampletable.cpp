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
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
    twMeas->setMaximumWidth(350);
    twMeas->setMinimumWidth(280);
    layout->addWidget(twMeas);
    twMeas->model()->removeRows(0,10);

    delegate = new delegate_sample();
    twMeas->setItemDelegate(delegate);

    connect(twMeas, SIGNAL(clicked(QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(twMeas, SIGNAL(activated(QModelIndex)), SLOT(changeRow(QModelIndex)));
}

void sampletable::getFileSample()
{
    stMainParam curMainParam;
    quint8  kolVo=0;
    quint8 Val;
    QByteArray Sample;
    QList <quint16> extremum;
    QList <quint16> mainParam;
    QStandardItemModel *model;
    model = (QStandardItemModel*)twMeas->model();
    model->setRowCount(0);

    QStringList fileNames = QFileDialog::getOpenFileNames(this, "select files");
    QFile file;
    bool bOk;
    foreach(QString fileName, fileNames)
    {
        Sample.clear();
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        file.read(144);
        while (!file.atEnd())
        {
            Val = (file.read(1).toHex().toUInt(&bOk, 16));
            file.read(1);
            Sample.append(Val);
        }
        file.close();
        extremum.clear();
        mainParam.clear();
        if (findExtremum(&Sample, extremum))
        {
            if(findMainParam(&extremum, curMainParam))
            {
                QStandardItem *ttt = new QStandardItem();
                model->appendRow(ttt);
                twMeas->model()->setData(twMeas->model()->index(kolVo, 0), kolVo, Qt::DisplayRole);
                twMeas->model()->setData(twMeas->model()->index(kolVo, 0), Sample, Qt::UserRole);
                twMeas->model()->setData(twMeas->model()->index(kolVo, 1), fileName, Qt::DisplayRole);
                refreshTable(kolVo, curMainParam);
            }
        }
        kolVo++;
    }
}

bool sampletable::findExtremum(QByteArray *Sample, QList<quint16> &extremum)
{
#define sampleStart 5
#define sampleEnd   1024
#define pik         (255*0.9)
#define spad        (60)
    quint16 kolvo = 0;
    bool front = true;
    foreach (quint8 val, *Sample)
    {
        if(kolvo>sampleStart)
        {
            if(val>pik)
            {
                if (front)
                {
                    for(int i=1; i<=5; i++)
                    {
                        if(((quint8)(Sample->at(kolvo-i)))<spad)
                        {
                            extremum.append((kolvo-i)+1);
                            break;
                        }
                    }
                }
                front = false;
            }
            else
            {
                if(val<spad)
                    front = true;
            }
        }
        kolvo++;
        if(kolvo>sampleEnd)
            break;
    }
    allExtremum = extremum;
    return (extremum.count()>=3?true:false) ;
}

bool sampletable::findMainParam(QList<quint16> *extremum, stMainParam &mainParam)
{
    quint16 Start, L1, L2, Retina, val;
    Start=L1=L2=Retina=0;
    for(int i=0; i<extremum->count();i++)
    {
        val = extremum->at(i);
        if(Start==0)
            Start = val;
        if((L1==0)&&(val>(Start+54))&&(val<(Start+162)))
            L1 = val;
        if((L2==0)&&(val>(L1+54))&&(val<(L1+162)))
            L2 = val;
        if((Retina==0)&&(val>(Start+459)))
            Retina = val;
    }
    if((Start>0)&&(L1>0)&&(L2>0)&&(Retina>0))
    {
        mainParam.Start = Start;
        mainParam.L1 = L1;
        mainParam.L2 = L2;
        mainParam.Retina = Retina;
        return true;
    }
    else
        return false;
}

/*
QList <double> Plot::intToMM(QList<quint16> *mainParam)
{
    QList <double> ret;
    ret.clear();
    ret.append((double)(round(mainParam->at(0)*100/27)/100));
    ret.append((double)(round(mainParam->at(1)*100/27)/100));
    ret.append((double)(round(mainParam->at(2)*100/27)/100));
    ret.append((double)(round(mainParam->at(3)*100/27)/100));
    return ret;
}
*/

void sampletable::refreshTable(stMainParam mainParam)
{
    qDebug()<<"refreshTable1";
    refreshTable((quint8)tableIndex.row(), mainParam);
}


void sampletable::refreshTable(quint8 rowNom, stMainParam mainParam)
{
    double sumAl, curAl, devAl;
    quint8 modelCount;

    qDebug()<<"refreshTable2";

    resultParam.ACD = decRound(mainParam.L1 - mainParam.Start, 2);
    resultParam.LT = decRound(mainParam.L2 - mainParam.L1, 2);
    resultParam.AL = decRound(mainParam.Retina - mainParam.Start, 2);
    resultParam.Vit = decRound(mainParam.Retina - mainParam.L2, 2);

    twMeas->model()->setData(twMeas->model()->index(rowNom, 2), resultParam.AL,  Qt::DisplayRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 2), mainParam.Start, Qt::UserRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 3), resultParam.ACD, Qt::DisplayRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 3), mainParam.L1,    Qt::UserRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 4), resultParam.LT,  Qt::DisplayRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 4), mainParam.L2,    Qt::UserRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 5), resultParam.Vit, Qt::DisplayRole);
    twMeas->model()->setData(twMeas->model()->index(rowNom, 5), mainParam.Retina,Qt::UserRole);

    modelCount = sumAl = devAl = 0;
    for (int i=0; i<10; i++)
    {
        curAl = 0;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            sumAl += curAl;
            modelCount++;
        }
    }

    if(modelCount>0)
    {
        sumAl = (sumAl/modelCount);
        sumAl *= 100;
        sumAl =  round(sumAl);
        sumAl /= 100;
    }

    for (int i=0; i<10; i++)
    {
        curAl = 0;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            if(sumAl>curAl)
            {
                if(devAl < (sumAl-curAl))
                    devAl = sumAl-curAl;
            }
            else
            {
                if(devAl < (curAl-sumAl))
                    devAl = curAl-sumAl;
            }
        }
    }

    AL =  decRound(twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 5), Qt::UserRole).toDouble(), 2);
    AL -= decRound(twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 2), Qt::UserRole).toDouble(), 2);
//    pBigView->setDisplay(AL, sumAl , devAl);
    resultParam.AL = AL;
    resultParam.sumAl = sumAl;
    resultParam.devAl = devAl;
//    emit (refreshMainParam());
    refreshResult(rowNom);
}

double sampletable::decRound(double Val, quint8 dec)
{
    Val *= pow(10, dec);
    Val /=27;
    Val = round(Val);
    Val /= pow(10, dec);
    return Val;
}

void sampletable::changeRow(QModelIndex curIndex)
{
    QList<quint16> extremum;

    tableIndex = curIndex;

    curIndex = twMeas->model()->index(curIndex.row(), 0);
    baSample=(twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    mainParam.Start = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L1 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L2 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.Retina = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());

//    foreach (quint8 val, baTmp)
//    {
//        hSample.insert(kolvo, val);
//        x[kolvo] = kolvo;
//        y[kolvo] = double(val);
//        kolvo++;
//    }



//    pPlot->drawSample(x, y, 1000);

//    if(pPlot->findExtremum(&baTmp, extremum))
//    {
//        pPlot->drawMarker(mainParam.Start, "Start");
//        pPlot->drawMarker((double)mainParam.Start,(double)60, Qt::yellow);
//        pPlot->drawMarker(mainParam.L1, "L1");
//        pPlot->drawMarker((double)mainParam.L1,(double)60, Qt::yellow);
//        pPlot->drawMarker(mainParam.L2, "L2");
//        pPlot->drawMarker((double)mainParam.L2,(double)60, Qt::yellow);
//        pPlot->drawMarker(mainParam.Retina, "Retina");
//        pPlot->drawMarker((double)mainParam.Retina,(double)60, Qt::yellow);
//    }

//    if(findExtremum(&baTmp, extremum))

//    AL =  (twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 5), Qt::UserRole).toDouble());
//    AL -= (twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 2), Qt::UserRole).toDouble());
 //   AL = decRound(AL, 2);
//    pBigView->setDisplay(AL);

    extremum.clear();
    findExtremum(&baSample, extremum);

    qDebug()<<"changeRow";

    emit(changeRow(extremum));

    refreshResult(twMeas->currentIndex().row());
}


void sampletable::refreshResult(quint8 rowNom)
{
    double sumAl, curAl, devAl, sd;
    quint8 modelCount;

    resultParam.ACD = twMeas->model()->data(twMeas->model()->index(rowNom, 3), Qt::DisplayRole).toDouble();
    resultParam.LT =  twMeas->model()->data(twMeas->model()->index(rowNom, 4), Qt::DisplayRole).toDouble();
    resultParam.AL =  twMeas->model()->data(twMeas->model()->index(rowNom, 2), Qt::DisplayRole).toDouble();
    resultParam.Vit = twMeas->model()->data(twMeas->model()->index(rowNom, 5), Qt::DisplayRole).toDouble();

    modelCount = sumAl = devAl = 0;
    for (int i=0; i<10; i++)
    {
        curAl = 0;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            sumAl += curAl;
            modelCount++;
        }
    }

    if(modelCount>0)
    {
        sumAl = (sumAl/modelCount);
        sumAl *= 100;
        sumAl =  round(sumAl);
        sumAl /= 100;
    }

    sd = 0;
    for (int i=0; i<10; i++)
    {
        curAl = 0;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            if(sumAl>curAl)
            {
                if(devAl < (sumAl-curAl))
                    devAl = sumAl-curAl;
            }
            else
            {
                if(devAl < (curAl-sumAl))
                    devAl = curAl-sumAl;
            }
            sd += qPow(devAl, 2);
        }
    }

    sd /= modelCount;
    sd = qPow(sd, 0.5);
    sd = decRound(sd, 4);

    for (int i=0; i<10; i++)
    {
                double curDev;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            curDev = round(abs(curAl*100 - sumAl*100));
            curDev /= 100;

            qDebug()<<curAl;
            qDebug()<<sd;
        }
                twMeas->model()->setData(twMeas->model()->index(i, 1), curDev, Qt::DisplayRole);
    }

    resultParam.sumAl = sumAl;
    resultParam.devAl = devAl;
    resultParam.countSample = modelCount;
    resultParam.SD = sd;

    emit (refreshMainParam());
}

void sampletable::delSample()
{
    twMeas->model()->removeRow(twMeas->currentIndex().row());
    refreshResult(twMeas->currentIndex().row());
}
