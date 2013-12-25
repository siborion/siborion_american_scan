#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;

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
    columnPercent<<33<<33<<34;
    twLens->setColumnPercent(columnPercent);

    columnPercent.clear();
    columnPercent<<50<<50;
    twVelocity->setColumnPercent(columnPercent);

    twPatient->verticalHeader()->hide();
    twPatient->horizontalHeader()->hide();
    twPatient->setMaximumHeight(120);
    twPatient->setFrameShape(QFrame::NoFrame);
    twPatient->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twPatient->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    twLens->verticalHeader()->hide();
    twLens->horizontalHeader()->hide();
    twLens->setMaximumHeight(120);
    twLens->setFrameShape(QFrame::NoFrame);
    twLens->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twLens->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    twVelocity->verticalHeader()->hide();
    twVelocity->horizontalHeader()->hide();
    twVelocity->setMaximumHeight(120);
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
    modelVelocity->setRowCount(4);

    twPatient->setModel(modelPatient);
    twLens->setModel(modelLens);
    twVelocity->setModel(modelVelocity);

    layoutTop->addWidget(twPatient);
    layoutTop->addItem(vs0);
    layoutTop->addWidget(twLens);
    layoutTop->addItem(vs1);
    layoutTop->addWidget(twVelocity);

//----------------------------------------- Button
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
    layoutBotLeft->setSpacing(0);
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



    ScanPlot *pPlot = new ScanPlot();



    layoutBot->addLayout(layoutBotLeft);
    layoutBot->addWidget(pPlot);
    layout->addLayout(layoutTop);
    layout->addLayout(layoutBot);
}
