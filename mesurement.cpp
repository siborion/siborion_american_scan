#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout     = new QGridLayout(this);
    QGridLayout *layoutDown = new QGridLayout();
    QGridLayout *layoutDown1= new QGridLayout();
    QGridLayout *layoutDown2= new QGridLayout();
    QGridLayout *layoutDown3= new QGridLayout();
    QPushButton *btStart    = new QPushButton();
    QPushButton *btFreez    = new QPushButton();
    QPushButton *btImersion = new QPushButton();
    QPushButton *btArhakic  = new QPushButton();
    QPushButton *btContact  = new QPushButton();
    QPushButton *btCataract = new QPushButton();
    QPushButton *btLeft     = new QPushButton();
    QPushButton *btRight    = new QPushButton();
    QSpacerItem *vs0 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vs1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vs2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vs3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QTableWidget *tbLastMeas = new QTableWidget(10, 3);
    QStringList lst;
    lst << "d" << "f" << "h";
    tbLastMeas->setHorizontalHeaderLabels(lst);
    tbLastMeas->setColumnWidth(0,50);
    tbLastMeas->setColumnWidth(1,50);
    tbLastMeas->setColumnWidth(2,50);

    tbLastMeas->setMaximumWidth(200);

    layout->addLayout    (layoutDown,  0, 0, 1, 1);
    layoutDown->addLayout(layoutDown1, 0, 0, 1, 1);
    layoutDown->addLayout(layoutDown2, 0, 2, 1, 1);
    layoutDown->addLayout(layoutDown3, 0, 3, 1, 1);

    btStart->setText("Start");
    btFreez->setText("Freez");
    btImersion->setText("Imersion");
    btArhakic->setText("Arhakic");
    btContact->setText("Contact");
    btCataract->setText("Catatract");
    btLeft->setText("Left");
    btRight->setText("Right");

    ScanPlot *p_scan = new ScanPlot();

    layoutDown1->addItem(vs0,          0, 0, 1, 1);
    layoutDown1->addWidget(btStart,    1, 0, 1, 1);
    layoutDown1->addWidget(btFreez,    2, 0, 1, 1);
    layoutDown1->addItem(vs1,          3, 0, 1, 1);
    layoutDown1->addWidget(btImersion, 4, 0, 1, 1);
    layoutDown1->addWidget(btArhakic,  5, 0, 1, 1);
    layoutDown1->addWidget(btContact,  6, 0, 1, 1);
    layoutDown1->addWidget(btCataract, 7, 0, 1, 1);
    layoutDown1->addItem(vs2,          8, 0, 1, 1);
    layoutDown1->addWidget(btLeft,     9, 0, 1, 1);
    layoutDown1->addWidget(btRight,    10,0, 1, 1);
    layoutDown1->addItem(vs3,          11,0, 1, 1);
    layoutDown2->addWidget( p_scan, 0, 0, 1, 1 );
    layoutDown3->addWidget( tbLastMeas, 0, 0, 1, 1 );

}
