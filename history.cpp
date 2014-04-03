#include "history.h"

history::history(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();

    QList<int> columnPercent;
    QStringList lst;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QVBoxLayout *layoutRight = new QVBoxLayout();
    QHBoxLayout *layoutBot = new QHBoxLayout();

    pBigView = new bigviewnumhor();
    pBigView->setMinimumHeight(70);
    pBigView->setMaximumHeight(100);
    qDebug() << pBigView->minimumHeight();
    qDebug() << pBigView->maximumHeight();


    QFrame *fmTop = new QFrame();
    fmTop->setFrameShape(QFrame::WinPanel);
    fmTop->setFrameShadow(QFrame::Raised);


    QFrame *fmPlot = new QFrame();
    fmPlot->setFrameShape(QFrame::WinPanel);
    fmPlot->setFrameShadow(QFrame::Raised);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this);
    glPlot->addWidget(pPlot);


    QTreeWidget *treeWidget = new QTreeWidget();
    QList <QTreeWidgetItem*> pItem;
    QTreeWidgetItem *pItemTmp;

    pItem.append(addItem("Dr.Ivanov"));
    pItem.append(addItem(pItem.last(), "Patient 1"));
    pItem.append(addItem(pItem.last(), "01.01.2014"));
    pItemTmp = pItem.last();
    pItem.append(addItem(pItemTmp, "Session 1"));
    pItem.append(addItem(pItemTmp, "Session 2"));
    pItem.append(addItem(pItemTmp, "Session 3"));
    pItem.append(addItem(pItemTmp, "Session 4"));

    pItem.append(addItem("Dr.Petrov"));
    pItem.append(addItem(pItem.last(), "Patient 2"));
    pItem.append(addItem(pItem.last(), "01.01.2014"));
    pItemTmp = pItem.last();
    pItem.append(addItem(pItemTmp, "Session 1"));
    pItem.append(addItem(pItemTmp, "Session 2"));
    pItem.append(addItem(pItemTmp, "Session 3"));
    pItem.append(addItem(pItemTmp, "Session 4"));

    treeWidget->addTopLevelItems(pItem);

//    pItemChild.append(addItem(pItem.last(), ""));
//    pItemChild.last()->setData(0, Qt::DisplayRole, tr("Вх.1,2"));
//    pItemChild.last()->setData(0, Qt::UserRole, ob_info::input);
//    treeWidget->setItemWidget(pItemChild.last(), 1, new ob_info_interval());




    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
    twMeas->setMinimumWidth(250);

    QPushButton *pbOd = new QPushButton(tr("OD"));
    QFont font;
    font.setPointSize(24);
    font.setBold(true);
    font.setWeight(75);
    pbOd->setFont(font);


    layoutBot->addWidget(fmPlot, 5);
    layoutBot->addLayout(layoutRight, 1);

    layoutTop->addWidget(pbOd);
    layoutTop->addWidget(pBigView);

    layoutRight->addWidget(treeWidget);
    layoutRight->addWidget(twMeas);

    layout->addLayout(layoutTop, 1);
    layout->addLayout(layoutBot, 2);
    layout->setStretch(0, 0);
    layout->setStretch(1, 1);

    connect(twMeas, SIGNAL(clicked(QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), SLOT(refreshTable(stMainParam)));
}

void history::getFileSample()
{
    stMainParam curMainParam;
    quint8  kolVo=0;
    quint8 Val;
    QByteArray Sample;
    QList <quint16> extremum;
    QList <quint16> mainParam;

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
        if (pPlot->findExtremum(&Sample, extremum))
        {
            if(pPlot->findMainParam(&extremum, curMainParam))
            {
                twMeas->model()->setData(twMeas->model()->index(kolVo, 0), kolVo, Qt::DisplayRole);
                twMeas->model()->setData(twMeas->model()->index(kolVo, 0), Sample, Qt::UserRole);
                twMeas->model()->setData(twMeas->model()->index(kolVo, 1), fileName, Qt::DisplayRole);
                refreshTable(kolVo, curMainParam);
            }
        }
        kolVo++;
    }
}

void history::changeRow(QModelIndex curIndex)
{
    stMainParam mainParam;
    QList<quint16> extremum;
    quint16 kolvo;
    double x[2048];
    double y[2048];
    kolvo=0;

    tableIndex = curIndex;

    QByteArray baTmp;

    curIndex = twMeas->model()->index(curIndex.row(), 0);
    baTmp.append(twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+2);
    mainParam.Start = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L1 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.L2 = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());
    curIndex = twMeas->model()->index(curIndex.row(), curIndex.column()+1);
    mainParam.Retina = (twMeas->model()->data(curIndex, Qt::UserRole).toInt());

    foreach (quint8 val, baTmp)
    {
        x[kolvo] = kolvo;
        y[kolvo] = double(val);
        kolvo++;
    }
    pPlot->drawSample(x, y, 1000);

    if(pPlot->findExtremum(&baTmp, extremum))
    {
        pPlot->drawMarker(mainParam.Start, "Start");
        pPlot->drawMarker((double)mainParam.Start,(double)60, Qt::yellow);
        pPlot->drawMarker(mainParam.L1, "L1");
        pPlot->drawMarker((double)mainParam.L1,(double)60, Qt::yellow);
        pPlot->drawMarker(mainParam.L2, "L2");
        pPlot->drawMarker((double)mainParam.L2,(double)60, Qt::yellow);
        pPlot->drawMarker(mainParam.Retina, "Retina");
        pPlot->drawMarker((double)mainParam.Retina,(double)60, Qt::yellow);
    }

    AL =  (twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 5), Qt::UserRole).toDouble());
    AL -= (twMeas->model()->data(twMeas->model()->index(twMeas->currentIndex().row(), 2), Qt::UserRole).toDouble());
    AL = decRound(AL, 2);
    pBigView->setDisplay(AL);

}

void history::refreshTable(stMainParam mainParam)
{
    refreshTable((quint8)tableIndex.row(), mainParam);
}

void history::refreshTable(quint8 rowNom, stMainParam mainParam)
{
    double sumAl, curAl, devAl;
    quint8 modelCount;

    stResultParam resultParam;
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
    pBigView->setDisplay(AL, sumAl , devAl);
}

double history::decRound(double Val, quint8 dec)
{
    Val *= pow(10, dec);
    Val /=27;
    Val = round(Val);
    Val /= pow(10, dec);
    return Val;
}

void history::save()
{
    qDebug() << "Save";
    pBaseFill->saveData();
}

QTreeWidgetItem* history::addItem(QString name)
{
  QStringList lst;
  lst << name;
  QTreeWidgetItem* pItem = new QTreeWidgetItem(treeWidget, lst, 0);
  return pItem;
}
QTreeWidgetItem* history::addItem(QTreeWidgetItem* item, QString name)
{
  QStringList lst;
  lst << name;
  QTreeWidgetItem* pItem = new QTreeWidgetItem(item, lst, 0);
  return pItem;
}
