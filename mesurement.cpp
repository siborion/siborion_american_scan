#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model = new QStandardItemModel();

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QVBoxLayout *layoutTopLeft = new QVBoxLayout();
    QHBoxLayout *layoutBot = new QHBoxLayout();
    QVBoxLayout *layoutBotLeft = new QVBoxLayout();

//------------------------------------ TableView
    columnPercent.clear();
    columnPercent<<50<<50;
    twPatient  = new adjview(4, 2, columnPercent);

//    QSpacerItem *vs0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    columnPercent.clear();
    columnPercent<<60<<20<<20;
    twLens     = new adjview(4, 3, columnPercent);

//    QSpacerItem *vs1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    columnPercent.clear();
    columnPercent<<80<<20;
    twVelocity = new adjview(3, 2, columnPercent);

//    twPatient->setMaximumHeight(120);
//    twPatient->setMinimumHeight(120);
//    twLens->setMaximumHeight(120);
//    twLens->setMinimumHeight(120);
//    twVelocity->setMaximumHeight(120);
//    twVelocity->setMinimumHeight(120);

    layoutTopLeft->addWidget(twPatient);
//    layoutTop->addItem(vs0);
    layoutTopLeft->addWidget(twLens);
//    layoutTop->addItem(vs1);
    layoutTopLeft->addWidget(twVelocity);

    model = (QStandardItemModel*)twPatient->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapPatient[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }

    model = (QStandardItemModel*)twLens->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapLens[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
        model->setItem(i, 2, new QStandardItem("mm"));
        model->item   (i, 2)->setBackground(Qt::lightGray);
        model->item   (i, 2)->setEditable(false);
    }

    model = (QStandardItemModel*)twVelocity->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapVelocity[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }

//----------------------------------------- Button
    QSpacerItem *hs = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *pbOd = new QPushButton(tr("OD"));
    QSpacerItem *hs0 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *pbMeasure = new QPushButton(tr("Measure"));
    QSpacerItem *hs1 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *pbAutoFreeze = new QPushButton(tr("Auto Freeze"));
    QPushButton *pbAuto = new QPushButton(tr("Auto"));
    QPushButton *pbManual = new QPushButton(tr("Manual"));
    QSpacerItem *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *pbContact = new QPushButton(tr("Contact"));
    QPushButton *pbImmersion = new QPushButton(tr("Immersion"));
    QSpacerItem *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *pbCataract = new QPushButton(tr("Cataract"));
    QPushButton *pbAphakic = new QPushButton(tr("Aphakic"));
    QSpacerItem *hs4 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);

    layoutBotLeft->setSpacing(0);
    layoutBotLeft->addItem(hs);
    layoutBotLeft->addWidget(pbOd);
    layoutBotLeft->addItem(hs0);
    layoutBotLeft->addWidget(pbMeasure);
    layoutBotLeft->addItem(hs1);
    layoutBotLeft->addWidget(pbAutoFreeze);
    layoutBotLeft->addWidget(pbAuto);
    layoutBotLeft->addWidget(pbManual);
    layoutBotLeft->addItem(hs2);
    layoutBotLeft->addWidget(pbContact);
    layoutBotLeft->addWidget(pbImmersion);
    layoutBotLeft->addItem(hs3);
    layoutBotLeft->addWidget(pbCataract);
    layoutBotLeft->addWidget(pbAphakic);
    layoutBotLeft->addItem(hs4);

    pPlot = new Plot(this);

//    pQwt = pPlot->q_plot;

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);

    layoutTop->addItem(layoutTopLeft);
    layoutTop->addWidget(twMeas);
    layoutTop->setStretch(0, 1);
    layoutTop->setStretch(1, 2);

    layoutBot->addLayout(layoutBotLeft,0);
    layoutBot->addWidget(pPlot,1);
//    layoutTopLeft->addWidget(pbTest);
    layout->addLayout(layoutTop);

    layout->addLayout(layoutBot);

    connect(pbAuto, SIGNAL(clicked()), SLOT(getFileSample()));
    connect(twMeas, SIGNAL(clicked(QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), SLOT(refreshTable(stMainParam)));
}

void mesurement::getFileSample()
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

void mesurement::changeRow(QModelIndex curIndex)
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
        foreach(int val, extremum)
        {
            pPlot->drawMarker((double)val,(double)(quint8)baTmp.at(val), Qt::yellow);
        }
        pPlot->drawMarker(mainParam.Start, "Start");
        pPlot->drawMarker(mainParam.L1, "L1");
        pPlot->drawMarker(mainParam.L2, "L2");
        pPlot->drawMarker(mainParam.Retina, "Retina");
    }
}


void mesurement::refreshTable(stMainParam mainParam)
{
    refreshTable((quint8)tableIndex.row(), mainParam);
}


void mesurement::refreshTable(quint8 rowNom, stMainParam mainParam)
{
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
    twMeas->model()->setData(twMeas->model()->index(rowNom, 5), mainParam.Retina,    Qt::UserRole);
}

double mesurement::decRound(double Val, quint8 dec)
{
    Val *= pow(10, dec);
    Val /=27;
    Val = round(Val);
    Val /= pow(10, dec);
    return Val;
}


