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
    twName->setMaximumHeight(90);
//-------------------------------
    columnPercent.clear();
    columnPercent<<15<<15<<15<<15<<15<<25;
    twLens = new adjview(8, 6, columnPercent);
    twLens->setMaximumHeight(240);
//-------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twK = new adjview(4, 2, columnPercent);
    twK->setMaximumHeight(120);
//-------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twA = new adjview(4, 2, columnPercent);
    twA->setMaximumHeight(120);

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
    columnPercent<<20<<80;
    twCalculator = new adjview(4, 2, columnPercent);
  
    layout->addWidget(twCalculator);

}
