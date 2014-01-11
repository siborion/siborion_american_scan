#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QHBoxLayout *layoutBot = new QHBoxLayout();
    QVBoxLayout *layoutBotLeft = new QVBoxLayout();

//------------------------------------ TableView
    twPatient  = new adjview();
    QSpacerItem *vs0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    twLens     = new adjview();
    QSpacerItem *vs1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    twVelocity = new adjview();

    columnPercent.clear();
    columnPercent<<50<<50;
    twPatient->setColumnPercent(columnPercent);

    columnPercent.clear();
    columnPercent<<60<<20<<20;
    twLens->setColumnPercent(columnPercent);

    columnPercent.clear();
    columnPercent<<80<<20;
    twVelocity->setColumnPercent(columnPercent);

    twPatient->verticalHeader()->hide();
    twPatient->horizontalHeader()->hide();
    twPatient->setMaximumHeight(120);
    twPatient->setMinimumHeight(120);
    twPatient->setFrameShape(QFrame::NoFrame);
    twPatient->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twPatient->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    twLens->verticalHeader()->hide();
    twLens->horizontalHeader()->hide();
    twLens->setMaximumHeight(120);
    twLens->setMinimumHeight(120);
    twLens->setFrameShape(QFrame::NoFrame);
    twLens->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twLens->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    twVelocity->verticalHeader()->hide();
    twVelocity->horizontalHeader()->hide();
    twVelocity->setMaximumHeight(120);
    twVelocity->setMinimumHeight(120);
    twVelocity->setFrameShape(QFrame::NoFrame);
    twVelocity->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twVelocity->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    modelPatient  = new QStandardItemModel();
    modelLens     = new QStandardItemModel();
    modelVelocity = new QStandardItemModel();

    modelPatient->setColumnCount(2);
    modelLens->setColumnCount(3);
    modelVelocity->setColumnCount(2);

    modelPatient->setRowCount(4);
    modelLens->setRowCount(4);
    modelVelocity->setRowCount(3);

    twPatient->setModel(modelPatient);
    twLens->setModel(modelLens);
    twVelocity->setModel(modelVelocity);

    layoutTop->addWidget(twPatient);
    layoutTop->addItem(vs0);
    layoutTop->addWidget(twLens);
    layoutTop->addItem(vs1);
    layoutTop->addWidget(twVelocity);

    for(quint8 i=0; i<4; i++)
    {
        modelPatient->setItem(i, 0, new QStandardItem(baseMapPatient[i]));
        modelPatient->item   (i, 0)->setBackground(Qt::lightGray);
        modelPatient->item   (i, 0)->setEditable(false);
    }

    for(quint8 i=0; i<4; i++)
    {
        modelLens->setItem(i, 0, new QStandardItem(baseMapLens[i]));
        modelLens->item   (i, 0)->setBackground(Qt::lightGray);
        modelLens->item   (i, 0)->setEditable(false);
        modelLens->setItem(i, 2, new QStandardItem("mm"));
        modelLens->item   (i, 2)->setBackground(Qt::lightGray);
        modelLens->item   (i, 2)->setEditable(false);
    }

    for(quint8 i=0; i<3; i++)
    {
        modelVelocity->setItem(i, 0, new QStandardItem(baseMapVelocity[i]));
        modelVelocity->item   (i, 0)->setBackground(Qt::lightGray);
        modelVelocity->item   (i, 0)->setEditable(false);
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


    ScanPlot *pPlot = new ScanPlot();

    twMeas  = new adjview();
    twMeas->verticalHeader()->hide();
    modelMeas  = new QStandardItemModel();
    modelMeas->setRowCount(10);
    modelMeas->setColumnCount(6);
    twMeas->setModel(modelMeas);
    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    modelMeas->setHorizontalHeaderLabels(lst);
    twMeas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twMeas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twMeas->setMaximumHeight(325);
    twMeas->setMinimumHeight(325);
    twMeas->setColumnPercent(columnPercent);


    layoutBot->addLayout(layoutBotLeft,0);
    layoutBot->addWidget(pPlot,1);
    layoutBot->addWidget(twMeas,0);
    layout->addLayout(layoutTop);
    layout->addLayout(layoutBot);
}
