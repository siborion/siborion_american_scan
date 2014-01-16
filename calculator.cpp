#include "calculator.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();
    QVBoxLayout *layoutTopLeft       = new QVBoxLayout();
    QHBoxLayout *layoutTopLeftDown   = new QHBoxLayout();
    QHBoxLayout *layoutGroupBox      = new QHBoxLayout();

    columnPercent.clear();
    columnPercent<<50<<50;
    twName = new adjview(3, 2, columnPercent);
    twName->verticalHeader()->setDefaultSectionSize(20);
    twName->setMinimumHeight(60);
    twName->setMaximumHeight(60);
    model = (QStandardItemModel*)twName->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapName[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //-------------------------------
    columnPercent.clear();
    columnPercent<<16<<16<<16<<16<<16<<20;
    lst<<"Lens Name"<<"Lens Mfg"<<"Mfg A-Const"<<"pAConst"<<"MfgACD"<<"pACD";
    twLens = new adjview(8, lst, columnPercent);
    twLens->verticalHeader()->setDefaultSectionSize(20);
    twLens->setMinimumHeight(160);
    twLens->setMaximumHeight(160);
    //-------------------------------
    columnPercent.clear();
    columnPercent<<40<<40<<20;
    twK = new adjview(4, 3, columnPercent);
    twK->verticalHeader()->setDefaultSectionSize(20);
    twK->setMinimumHeight(80);
    twK->setMaximumHeight(80);
    model = (QStandardItemModel*)twK->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapK[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
        model->setItem(i, 2, i==0?new QStandardItem("mm"):new QStandardItem("D"));
        model->item   (i, 2)->setBackground(Qt::lightGray);
        model->item   (i, 2)->setEditable(false);
    }
    //--------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twA = new adjview(4, 2, columnPercent);
    twA->verticalHeader()->setDefaultSectionSize(20);
    twA->setMinimumHeight(80);
    twA->setMaximumHeight(80);
    model = (QStandardItemModel*)twA->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapA[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //--------------------------------
    layoutTopLeftDown->addWidget(twK, 0, Qt::AlignTop);
    layoutTopLeftDown->addWidget(twA, 0, Qt::AlignTop);
    layoutTopLeft->addWidget(twName);
    layoutTopLeft->addLayout(layoutTopLeftDown);
    layoutTop->addLayout(layoutTopLeft);
    layoutTop->addWidget(twLens);
    layout->addLayout(layoutTop);
    //--------------------------------
    QGroupBox *groupBox = new QGroupBox("Primary Formula");
    groupBox->setLayout(layoutGroupBox);
    QRadioButton *rbSRKII = new QRadioButton("SRKII");
    QRadioButton *rbSRKT = new QRadioButton("SRK/T");
    QRadioButton *rbHofferQ = new QRadioButton("Hoffer Q");
    QRadioButton *rbHolladay = new QRadioButton("Holladay");

    layoutGroupBox->addWidget(rbSRKII);
    layoutGroupBox->addWidget(rbSRKT);
    layoutGroupBox->addWidget(rbHofferQ);
    layoutGroupBox->addWidget(rbHolladay);

    layout->addWidget(groupBox);
    //--------------------------------
    columnPercent.clear();
    columnPercent<<10<<10<<10<<10<<10<<10<<10<<10<<10<<10;
    twCalculator = new adjview(10, 10, columnPercent);
    twCalculator->verticalHeader()->setDefaultSectionSize(20);
    twCalculator->setMinimumHeight(200);
    twCalculator->setMaximumHeight(200);
    layout->addWidget(twCalculator);

    //--------------------------------
    columnPercent.clear();
    columnPercent<<20<<20<<20<<20<<20;
    twCalculator1 = new adjview(4, 5, columnPercent);
    twCalculator1->verticalHeader()->setDefaultSectionSize(20);
    twCalculator1->setMinimumHeight(80);
    twCalculator1->setMaximumHeight(80);


    layout->addWidget(twCalculator1);

}
