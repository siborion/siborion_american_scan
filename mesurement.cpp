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

    QSpacerItem *vs0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    columnPercent.clear();
    columnPercent<<60<<20<<20;
    twLens     = new adjview(4, 3, columnPercent);

    QSpacerItem *vs1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
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

//    QFont font;
//    font.setBold(true);
//    twMeas->model()->setData(twMeas->model()->index(1, 1), font, Qt::FontRole);

//    mydelegate *myDelegate = new mydelegate();
//    twMeas->setItemDelegate(myDelegate);
    //twMeas->setSelectionMode(QAbstractItemView::SelectRows);
//    twMeas->setMaximumHeight(350);
//    twMeas->setMinimumHeight(350);

//    QPushButton *pbTest = new QPushButton("Add samples");

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
}

void mesurement::getFileSample()
{
    quint16 L1, L2, Retina;
    quint8  kolVo=0;
    quint16 numByte;
    quint8 Val;
    QList <QByteArray> baListSample;
    QByteArray Sample;
    QStandardItemModel *model;

    QStringList fileNames = QFileDialog::getOpenFileNames();
    QFile file;
    bool bOk;
    model = (QStandardItemModel*)twMeas->model();
    foreach(QString fileName, fileNames)
    {
        Sample.clear();
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        file.read(144);
        numByte = 0;
        L1=L2=Retina=0;
        while (!file.atEnd())
        {
            Val = (file.read(1).toHex().toUInt(&bOk, 16));
            file.read(1);
            Sample.append(Val);

            if((Val>=230)&&(L1==0)&&(numByte>=54)&&(numByte<162))
                L1 = numByte;
            if((Val>=230)&&(L2==0)&&(numByte>=(L1+54))&&(numByte<(L1+162)))
                L2 = numByte;
            if((Val>=230)&&(Retina==0)&&(numByte>=(459)))
                Retina = numByte;

            numByte++;
        }
        file.close();
        baListSample << Sample;
        QStandardItem *item0 = new QStandardItem();
        QStandardItem *item1 = new QStandardItem();
        QStandardItem *item2 = new QStandardItem();
        item0->setData(kolVo,  Qt::DisplayRole);
        item1->setData(Sample, Qt::UserRole);
        item2->setData(fileName,  Qt::DisplayRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 0), kolVo, Qt::DisplayRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 0), Sample, Qt::UserRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 1), fileName, Qt::DisplayRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 3), (round(((double)L1/27)*100))/100, Qt::DisplayRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 4), (round(((double)(L2-L1)/27)*100))/100, Qt::DisplayRole);
        twMeas->model()->setData(twMeas->model()->index(kolVo, 2), (round(((double)Retina/27)*100))/100, Qt::DisplayRole);
        kolVo++;
    }
}

void mesurement::changeRow(QModelIndex curIndex)
{
    quint16 L1, L2, Retina, kolvo;
    double x[2048];
    double y[2048];
    L1=L2=Retina=kolvo=0;
    QByteArray baTmp;
    baTmp.append(twMeas->model()->data(curIndex, Qt::UserRole).toByteArray());
    foreach (quint8 val, baTmp)
    {
        x[kolvo] = kolvo;
        y[kolvo] = double(val);

        if((y[kolvo]>230)&&(L1==0)&&(kolvo>54)&&(kolvo<162))
            L1 = kolvo;

        if((y[kolvo]>230)&&(L2==0)&&(kolvo>(L1+54))&&(kolvo<(L1+162)))
            L2 = kolvo;

        if((y[kolvo]>230)&&(Retina==0)&&(kolvo>(459)))
            Retina = kolvo;

        kolvo++;
    }
    pPlot->drawSample(x, y, 1000);
    pPlot->drawMarker(0, L1);
    pPlot->drawMarker(1, L2);
    pPlot->drawMarker(2, Retina);
}

