#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model = new QStandardItemModel();

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutTop = new QHBoxLayout();
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

    twPatient->setMaximumHeight(120);
    twPatient->setMinimumHeight(120);
    twLens->setMaximumHeight(120);
    twLens->setMinimumHeight(120);
    twVelocity->setMaximumHeight(120);
    twVelocity->setMinimumHeight(120);

    layoutTop->addWidget(twPatient);
    layoutTop->addItem(vs0);
    layoutTop->addWidget(twLens);
    layoutTop->addItem(vs1);
    layoutTop->addWidget(twVelocity);

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

    ScanPlot *pPlot = new ScanPlot();

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setMaximumHeight(350);
    twMeas->setMinimumHeight(350);

    layoutBot->addLayout(layoutBotLeft,0);
    layoutBot->addWidget(pPlot,1);
    layoutBot->addWidget(twMeas,0);
    layout->addLayout(layoutTop);
    layout->addLayout(layoutBot);
}
