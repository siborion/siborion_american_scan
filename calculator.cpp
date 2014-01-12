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

    modelName = new QStandardItemModel();
    modelName->setRowCount(3);
    modelName->setColumnCount(2);
    twName = new adjview();
    twName->setModel(modelName);
    twName->verticalHeader()->hide();
    twName->horizontalHeader()->hide();
//    twName->setMaximumHeight(120);
//    twName->setMinimumHeight(120);
    twName->setFrameShape(QFrame::NoFrame);
    twName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<50<<50;
    twName->setColumnPercent(columnPercent);
    twName->setMaximumHeight(90);

    modelLens = new QStandardItemModel();
    modelLens->setRowCount(8);
    modelLens->setColumnCount(6);
    twLens = new adjview();
    twLens->setModel(modelLens);
    twLens->verticalHeader()->hide();
    twLens->horizontalHeader()->hide();
//    twLens->setMaximumHeight(120);
//    twLens->setMinimumHeight(120);
    twLens->setFrameShape(QFrame::NoFrame);
    twLens->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twLens->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<50<<50;
    twLens->setColumnPercent(columnPercent);
    twLens->setMaximumHeight(240);

    modelK = new QStandardItemModel();
    modelK->setRowCount(4);
    modelK->setColumnCount(2);
    twK = new adjview();
    twK->setModel(modelK);
    twK->verticalHeader()->hide();
    twK->horizontalHeader()->hide();
//    twK->setMaximumHeight(120);
//    twK->setMinimumHeight(120);
    twK->setFrameShape(QFrame::NoFrame);
    twK->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twK->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<50<<50;
    twK->setColumnPercent(columnPercent);
    twK->setMaximumHeight(120);

    modelA = new QStandardItemModel();
    modelA->setRowCount(4);
    modelA->setColumnCount(2);
    twA = new adjview();
    twA->setModel(modelA);
    twA->verticalHeader()->hide();
    twA->horizontalHeader()->hide();
//    twA->setMaximumHeight(120);
//    twA->setMinimumHeight(120);
    twA->setFrameShape(QFrame::NoFrame);
    twA->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<50<<50;
    twA->setColumnPercent(columnPercent);
    twA->setMaximumHeight(120);

    layoutTopLeftDown->addWidget(twK, 0, Qt::AlignTop);
    layoutTopLeftDown->addWidget(twA, 0, Qt::AlignTop);
    layoutTopLeft->addWidget(twName);
    layoutTopLeft->addLayout(layoutTopLeftDown);
    layoutTop->addLayout(layoutTopLeft);
    layoutTop->addWidget(twLens);
    layout->addLayout(layoutTop);


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


//    modelCalculator = new QStandardItemModel();
//    modelCalculator->setRowCount(4);
//    modelCalculator->setColumnCount(2);
    columnPercent.clear();
    columnPercent<<20<<80;
    twCalculator = new adjview(4, 2, columnPercent);
//    twCalculator->setModel(modelCalculator);
//    twCalculator->verticalHeader()->hide();
//    twCalculator->horizontalHeader()->hide();
//    twCalculator->setFrameShape(QFrame::NoFrame);
//    twCalculator->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    twCalculator->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    twCalculator->setColumnPercent(columnPercent);
//    twCalculator->setMaximumHeight(120);

    layout->addWidget(twCalculator);

}
