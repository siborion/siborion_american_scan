#include "calculator.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(Pal);

    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();
    QVBoxLayout *layoutTopLeft       = new QVBoxLayout();
    QHBoxLayout *layoutTopLeftDown   = new QHBoxLayout();
    QHBoxLayout *layoutGroupBox      = new QHBoxLayout();

    QSpacerItem *vs0 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *vs1 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *vs2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

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
//    layout->addItem(vs0);
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

    layout->addItem(vs0);
    layout->addWidget(groupBox);
    layout->addItem(vs1);
    //--------------------------------
//    columnPercent.clear();
//    columnPercent<<10<<10<<10<<10<<10<<10<<10<<10<<10<<10;
//    twCalculator = new adjview(10, 10, columnPercent);
//    twCalculator->verticalHeader()->setDefaultSectionSize(20);
//    twCalculator->setMinimumHeight(200);
//    twCalculator->setMaximumHeight(200);
//    twCalculator->setSpan(0, 0, 1, 2);
//    twCalculator->setSpan(0, 2, 1, 2);
//    twCalculator->setSpan(0, 4, 1, 2);
//    twCalculator->setSpan(0, 6, 1, 2);
//    twCalculator->setSpan(0, 8, 1, 2);
//    twCalculator->setSpan(1, 0, 1, 2);
//    twCalculator->setSpan(1, 2, 1, 2);
//    twCalculator->setSpan(1, 4, 1, 2);
//    twCalculator->setSpan(1, 6, 1, 2);
//    twCalculator->setSpan(1, 8, 1, 2);
//    model = (QStandardItemModel*)twCalculator->model();

//    QStandardItem *ac1 = new QStandardItem("A-Const= ,00");
//    ac1->setTextAlignment(Qt::AlignRight);
//    QStandardItem *ac2 = new QStandardItem("A-Const= ,00");
//    ac2->setTextAlignment(Qt::AlignRight);
//    QStandardItem *ac3 = new QStandardItem("A-Const= ,00");
//    ac3->setTextAlignment(Qt::AlignRight);
//    QStandardItem *ac4 = new QStandardItem("A-Const= ,00");
//    ac4->setTextAlignment(Qt::AlignRight);
//    QStandardItem *ac5 = new QStandardItem("A-Const= ,00");
//    ac5->setTextAlignment(Qt::AlignRight);

//    model->setItem(1, 0, ac1);
//    model->setItem(1, 2, ac2);
//    model->setItem(1, 4, ac3);
//    model->setItem(1, 6, ac4);
//    model->setItem(1, 8, ac5);
//    model->setItem(2, 0, new QStandardItem("IOL"));
//    model->setItem(2, 1, new QStandardItem("REF"));
//    model->setItem(2, 2, new QStandardItem("IOL"));
//    model->setItem(2, 3, new QStandardItem("REF"));
//    model->setItem(2, 4, new QStandardItem("IOL"));
//    model->setItem(2, 5, new QStandardItem("REF"));
//    model->setItem(2, 6, new QStandardItem("IOL"));
//    model->setItem(2, 7, new QStandardItem("REF"));
//    model->setItem(2, 8, new QStandardItem("IOL"));
//    model->setItem(2, 9, new QStandardItem("REF"));
//    model->setData()

//    layout->addWidget(twCalculator);
    //--------------------------------
//    columnPercent.clear();
//    columnPercent<<20<<20<<20<<20<<20;
//    twCalculator1 = new adjview(4, 5, columnPercent);
//    twCalculator1->verticalHeader()->setDefaultSectionSize(20);
//    twCalculator1->setMinimumHeight(80);
//    twCalculator1->setMaximumHeight(80);
//    layout->addWidget(twCalculator1);
//    layout->addItem(vs1);
//    mydelegate *ded = new mydelegate(true, this);
//    twCalculator->setItemDelegate(ded);

     frCalculator = new QFrame();
     frCalculator->setFrameShape(QFrame::WinPanel);
     frCalculator->setFrameShadow(QFrame::Raised);
     QGridLayout *frLayout = new QGridLayout(frCalculator);

     columnPercent.clear();
     columnPercent<<50<<50;
     lst.clear();
     lst<<"IOL"<<"REF";
     twCalculator1 = new adjview(10, lst, columnPercent);
     twCalculator1->verticalHeader()->setDefaultSectionSize(20);
     twCalculator1->setMinimumHeight(200);
     twCalculator1->setMaximumHeight(200);

     twCalculator2 = new adjview(10, lst, columnPercent);
     twCalculator2->verticalHeader()->setDefaultSectionSize(20);
     twCalculator2->setMinimumHeight(200);
     twCalculator2->setMaximumHeight(200);

     twCalculator3 = new adjview(10, lst, columnPercent);
     twCalculator3->verticalHeader()->setDefaultSectionSize(20);
     twCalculator3->setMinimumHeight(200);
     twCalculator3->setMaximumHeight(200);

     frLayout->addWidget(twCalculator1, 0, 0);
     frLayout->addWidget(twCalculator2, 0, 1);
     frLayout->addWidget(twCalculator3, 0, 2);

     layout->addWidget(frCalculator);
     layout->addItem(vs2);
}

