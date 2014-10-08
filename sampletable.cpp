#include "sampletable.h"
#include <QtCore/qmath.h>

sampletable::sampletable(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;
    curentParam = CurentParam::instanse();

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

    modelOD = new QStandardItemModel();
    modelOS = new QStandardItemModel();

    modelOD->setHorizontalHeaderLabels(lst);
    modelOS->setHorizontalHeaderLabels(lst);

    twMeas->setModel(modelOD);

    connect(twMeas, SIGNAL(clicked(QModelIndex)),   SLOT(changeRow(QModelIndex)));
    connect(twMeas, SIGNAL(activated(QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(curentParam, SIGNAL(changeSideSignal()), SLOT(changeSide()));
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
        file.read(146);
        while (!file.atEnd())
        {
            Val = (file.read(1).toHex().toUInt(&bOk, 16));
            file.read(1);
            Sample.append(Val);
        }
        file.close();
        extremum.clear();
        mainParam.clear();
        if (findExtremum(&Sample, extremum, curMainParam))
        {
            //            if(findMainParam(&extremum, curMainParam))
            //            {
            addSampleToTable(Sample, curMainParam);
            //            }
        }
        kolVo++;
    }
}

bool sampletable::findExtremum(QByteArray *Sample, QList<quint16> &extremum, stMainParam &mainParam)
{
    bool corneaEn, lens1En, lens2En, retinaEn;
    corneaEn = lens1En = lens2En =retinaEn = false;
    qint16 tmp;

    allExtremum.clear();

    parseCornea =  new  parserFront(curentParam->corneaX1, curentParam->corneaX2, 7, 0,  0);
    parseLens   =  new  parserFront(curentParam->lensX1,   curentParam->lensX2,   7, 27, 0);
    parseRetina =  new  parserFront(curentParam->retinaX1, curentParam->retinaX2, 7, 54, 0);

    for(int i=0; i<Sample->count(); i++)
    {
        tmp=parseCornea->parser(i,Sample->at(i));
        if(tmp>=0)
        {
            if(!corneaEn)
                mainParam.Start = tmp;
            corneaEn = true;
            extremum.append(tmp);
            qDebug()<<"Cornea"<<tmp;
        }

        tmp=parseLens->parser(i,Sample->at(i));
        if(tmp>=0)
        {
            if(!lens1En)
            {
                mainParam.L1 = tmp;
                lens1En = true;
            }
            else
            {
                if(!lens2En)
                {
                    mainParam.L2 = tmp;
                    lens2En = true;
                }
            }
            extremum.append(tmp);
            qDebug()<<"Lens"<<tmp;
        }

        tmp=parseRetina->parser(i,Sample->at(i));
        if(tmp>=0)
        {
            if(!retinaEn)
                mainParam.Retina = tmp;
            retinaEn = true;
            extremum.append(tmp);
            qDebug()<<"Retina"<<tmp;
        }
    }

    allExtremum = extremum;

    if(curentParam->cataract)
        return (corneaEn && lens1En && lens2En && retinaEn);
    else
        return (corneaEn && retinaEn);
}

/*
bool sampletable::findMainParam(QList<quint16> *extremum, stMainParam &mainParam)
{
    quint16 Start, L1, L2, Retina, val;
    Start=L1=L2=Retina=0;

    mainParam.Start=Start;
    mainParam.L1=L1;
    mainParam.L2=L2;
    mainParam.Retina=Retina;

    qDebug()<<"Start"<<Start;
    qDebug()<<"Retina"<<Retina;

    if((Start>0)&&(Retina>0))
        return true;
    else
        return false;
}
*/

void sampletable::refreshTable(stMainParam mainParam)
{
    refreshTable((quint8)tableIndex.row(), mainParam);
}

void sampletable::refreshTable(quint8 rowNom, stMainParam mainParam)
{
    double sumAl, curAl;
    double sumAcd, curAcd;
    double sumLt, curLt;
    double sumVit, curVit;
    double devAl, devAcd, devLt, devVit;
    quint8 modelCount;
    curAl = curAcd = curLt = curVit = 0;
    sumAl = sumAcd = sumLt = sumVit = 0;
    devAl = devAcd = devLt = devVit = 0;

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
    for (int i=0; i<twMeas->model()->rowCount(); i++)
    {
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        curAcd = twMeas->model()->data(twMeas->model()->index(i, 3), Qt::DisplayRole).toDouble();
        curLt = twMeas->model()->data(twMeas->model()->index(i, 4), Qt::DisplayRole).toDouble();
        curVit = twMeas->model()->data(twMeas->model()->index(i, 5), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {sumAl += curAl; modelCount++;}
        if(curAcd>0)
            sumAcd += curAcd;
        if(curLt>0)
            sumLt += curLt;
        if(curAcd>0)
            sumVit += curVit;
    }

    if(modelCount>0)
    {
        sumAl = (sumAl/modelCount); sumAl *= 100; sumAl =  round(sumAl); sumAl /= 100;
        sumAcd = (sumAcd/modelCount); sumAcd *= 100; sumAcd =  round(sumAcd); sumAcd /= 100;
        sumLt = (sumLt/modelCount); sumLt *= 100; sumLt =  round(sumLt); sumLt /= 100;
        sumVit = (sumVit/modelCount); sumVit *= 100; sumVit =  round(sumVit); sumVit /= 100;
    }

    for (int i=0; i<twMeas->model()->rowCount(); i++)
    {
        curAl = 0;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        curAcd = twMeas->model()->data(twMeas->model()->index(i, 3), Qt::DisplayRole).toDouble();
        curLt = twMeas->model()->data(twMeas->model()->index(i, 4), Qt::DisplayRole).toDouble();
        curVit = twMeas->model()->data(twMeas->model()->index(i, 5), Qt::DisplayRole).toDouble();

        if(curAl>0)
        {
            devAl  += pow((sumAl  - curAl), 2);
            devAcd += pow((sumAcd - curAcd), 2);
            devLt  += pow((sumLt  - curLt), 2);
            devVit += pow((sumVit - curVit), 2);
        }
    }

    devAl  = pow(devAl/twMeas->model()->rowCount(),  0.5);
    devAcd = pow(devAcd/twMeas->model()->rowCount(), 0.5);
    devLt  = pow(devLt/twMeas->model()->rowCount(),  0.5);
    devVit = pow(devVit/twMeas->model()->rowCount(), 0.5);

    AL =  decRound(twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 5), Qt::UserRole).toDouble(), 2);
    AL -= decRound(twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 2), Qt::UserRole).toDouble(), 2);

    resultParam.AL = AL;

    curentParam->measureAveAL  = resultParam.AvgAl = sumAl;
    curentParam->measureAveACD = resultParam.AvgAcd = sumAcd;
    curentParam->measureAveLT  = resultParam.AvgLt = sumLt;
    curentParam->measureAveVIT = sumVit;

    curentParam->measureDevAL  = resultParam.devAl  = devAl;
    curentParam->measureDevACD = resultParam.devAcd = devAcd;
    curentParam->measureDevLT  = resultParam.devLt  = devLt;
    curentParam->measureDevVIT = resultParam.devVit = devVit;

    refreshResult(rowNom);
}

void sampletable::changeSide()
{
    if(curentParam->sideOD)
        twMeas->setModel(modelOD);
    else
        twMeas->setModel(modelOS);

    qDebug()<<"twMeas->setModel(modelOS);";
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
    //    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    //    mainParam.Start = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    //    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    //    mainParam.L1 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    //    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    //    mainParam.L2 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    //    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    //    mainParam.Retina = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    //    extremum.clear();
    findExtremum(&baSample, extremum, mainParam);
    emit(changeRow(extremum));
    refreshResult(twMeas->currentIndex().row());
}

void sampletable::refreshResult(quint8 rowNom)
{
    double sumAl, curAl, devAl;
    quint8 modelCount;
    QColor color;

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

    for (int i=0; i<10; i++)
    {
        double curDev;
        curAl = twMeas->model()->data(twMeas->model()->index(i, 2), Qt::DisplayRole).toDouble();
        if(curAl>0)
        {
            curDev = round(abs(curAl*100 - sumAl*100));
            curDev /= 100;

            for(int j=0; j<=5; j++)
            {
                color.setNamedColor(curDev>=0.2?"yellow":"white");
                twMeas->model()->setData(twMeas->model()->index(i, j), color, Qt::BackgroundRole);
            }
        }
    }

    resultParam.AvgAl = sumAl;
    resultParam.devAl = devAl;
    resultParam.countSample = modelCount;
    emit (refreshMainParam());
}

void sampletable::delSample()
{
    quint8 curRow;
    curRow = twMeas->currentIndex().row();
    twMeas->model()->removeRow(curRow);
    twMeas->selectRow(curRow);
    changeRow(twMeas->currentIndex());
}

void sampletable::addSampleToTable(QByteArray Sample, stMainParam curMainParam)
{
    quint8 kolVo;
    QString fileName = "";
    QStandardItemModel *model;
    model = (QStandardItemModel*)twMeas->model();
    kolVo = twMeas->model()->rowCount();
    QStandardItem *ttt = new QStandardItem();
    model->appendRow(ttt);
    twMeas->model()->setData(twMeas->model()->index(kolVo, 0), kolVo, Qt::DisplayRole);
    twMeas->model()->setData(twMeas->model()->index(kolVo, 0), Sample, Qt::UserRole);
    twMeas->model()->setData(twMeas->model()->index(kolVo, 1), fileName, Qt::DisplayRole);
    refreshTable(kolVo, curMainParam);
}

stPrintSample sampletable::printSample()
{
    QModelIndex curIndex;
    stPrintSample tmp;

    curIndex = twMeas->model()->index(curIndex.row(), 0);
    baSample=(twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    mainParam.Start = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L1 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L2 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);

    curIndex = twMeas->model()->index(0, 0);
    tmp.sample1             = (twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    tmp.mainParam1.Start   = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam1.L1      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam1.L2      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam1.Retina  = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());

    curIndex = twMeas->model()->index(1, 0);
    tmp.sample2             = (twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    tmp.mainParam2.Start   = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam2.L1      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam2.L2      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam2.Retina  = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());

    curIndex = twMeas->model()->index(2, 0);
    tmp.sample3             = (twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    tmp.mainParam3.Start   = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam3.L1      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam3.L2      = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    tmp.mainParam3.Retina  = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());

    return tmp;
}
