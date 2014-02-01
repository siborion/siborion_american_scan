#include "calculator.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
//    QPalette Pal(palette());
//    Pal.setColor(QPalette::Background, Qt::gray);
//    setAutoFillBackground(true);
//    setPalette(Pal);

    QList<int> columnPercent;
    QStringList lst;
    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();
    QVBoxLayout *layoutTopLeft       = new QVBoxLayout();
    QGridLayout *layoutTopLeftDown   = new QGridLayout();

    QSpacerItem *vs2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    columnPercent.clear();
    columnPercent<<50<<50;
    twName = new adjview(3, 2, columnPercent);
    model = (QStandardItemModel*)twName->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapName[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //-------------------------------
    columnPercent.clear();
    columnPercent<<20<<16<<22<<16<<15<<11;
    lst<<"Lens Name"<<"Lens Mfg"<<"Mfg A-Const"<<"pAConst"<<"MfgACD"<<"pACD";
    twLens = new adjview(8, lst, columnPercent);
    //-------------------------------
    columnPercent.clear();
    columnPercent<<40<<40<<20;
    twK = new adjview(4, 3, columnPercent);
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
    model = (QStandardItemModel*)twA->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapA[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //--------------------------------

    pbOD = new QPushButton("OD");
    pbPersCalc = new QPushButton("Personalized Calculation");



    layoutTopLeftDown->addWidget(twK, 0, 0);
    layoutTopLeftDown->addWidget(twA, 0, 1);
    layoutTopLeftDown->addWidget(pbOD, 1, 0);
    layoutTopLeftDown->addWidget(pbPersCalc, 1, 1);

    layoutTopLeft->addWidget(twName);
    layoutTopLeft->addLayout(layoutTopLeftDown);
    layoutTop->addLayout(layoutTopLeft);
    layoutTop->addWidget(twLens);
    layout->addLayout(layoutTop);

     frCalculator = new QFrame();
     frCalculator->setFrameShape(QFrame::WinPanel);
     frCalculator->setFrameShadow(QFrame::Raised);
     QHBoxLayout *frLayout = new QHBoxLayout(frCalculator);

     Formula1 = new formula();
     Formula2 = new formula();
     Formula3 = new formula();

     frLayout->addWidget(Formula1);
     frLayout->addWidget(Formula2);
     frLayout->addWidget(Formula3);

//     columnPercent.clear();
//     columnPercent<<100;
//     lst.clear();
//     lst<<"U.D.";
//     twHead1 = new adjview(1, lst, columnPercent);
//     twHead2 = new adjview(1, lst, columnPercent);
//     twHead3 = new adjview(1, lst, columnPercent);

//     columnPercent.clear();
//     columnPercent<<50<<50;
//     lst.clear();
//     lst<<"IOL"<<"REF";
//     twCalculator1 = new adjview(10, lst, columnPercent);
//     twCalculator2 = new adjview(10, lst, columnPercent);
//     twCalculator3 = new adjview(10, lst, columnPercent);

//     lst.clear();
//     lst<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay";
//     cbFormula1 = new QComboBox();
//     cbFormula1->addItems(lst);
//     cbFormula2 = new QComboBox();
//     cbFormula2->addItems(lst);
//     cbFormula3 = new QComboBox();
//     cbFormula3->addItems(lst);

//     columnPercent.clear();
//     columnPercent<<100;
//     twVs1 = new adjview(lst, 1, columnPercent);
//     twVs2 = new adjview(lst, 1, columnPercent);
//     twVs3 = new adjview(lst, 1, columnPercent);

//     frLayout->setVerticalSpacing(0);
//     frLayout->addWidget(cbFormula1, 0, 0);
//     frLayout->addWidget(cbFormula2, 0, 1);
//     frLayout->addWidget(cbFormula3, 0, 2);
//     frLayout->addWidget(twHead1, 1, 0);
//     frLayout->addWidget(twHead2, 1, 1);
//     frLayout->addWidget(twHead3, 1, 2);
//     frLayout->addWidget(twCalculator1, 2, 0);
//     frLayout->addWidget(twCalculator2, 2, 1);
//     frLayout->addWidget(twCalculator3, 2, 2);
//     frLayout->addWidget(twVs1, 3, 0);
//     frLayout->addWidget(twVs2, 3, 1);
//     frLayout->addWidget(twVs3, 3, 2);

     layout->addWidget(frCalculator);
     layout->addItem(vs2);
}

