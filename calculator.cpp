#include "calculator.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;

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
//-------------------------------
    columnPercent.clear();
    columnPercent<<15<<15<<15<<15<<15<<25;
    twLens = new adjview(8, 6, columnPercent);
    twLens->verticalHeader()->setDefaultSectionSize(20);
    twLens->setMinimumHeight(160);
    twLens->setMaximumHeight(160);
//-------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twK = new adjview(4, 2, columnPercent);
    twK->verticalHeader()->setDefaultSectionSize(20);
    twK->setMinimumHeight(80);
    twK->setMaximumHeight(80);
//-------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twA = new adjview(4, 2, columnPercent);
    twA->verticalHeader()->setDefaultSectionSize(20);
    twA->setMinimumHeight(80);
    twA->setMaximumHeight(80);

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
