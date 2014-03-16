#include "key.h"

key::key(QWidget *parent) :
    QWidget(parent)
{
    //----------------------------------------- Button
    QHBoxLayout *layoutKey = new QHBoxLayout(this);

//    QSpacerItem *hs = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    QPushButton *pbOd = new QPushButton(tr("OD"));
    QSpacerItem *hs0 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *pbMeasure = new QPushButton(tr("Measure"));
    QSpacerItem *hs1 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *pbAutoFreeze = new QPushButton(tr("Auto Freeze"));
    QPushButton *pbAuto = new QPushButton(tr("Auto"));
    QPushButton *pbManual = new QPushButton(tr("Manual"));
    QSpacerItem *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *pbContact = new QPushButton(tr("Contact"));
    QPushButton *pbImmersion = new QPushButton(tr("Immersion"));
    QSpacerItem *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *pbCataract = new QPushButton(tr("Cataract"));
    QPushButton *pbAphakic = new QPushButton(tr("Aphakic"));
    QSpacerItem *hs4 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutKey->setSpacing(0);
//    layoutKey->addItem(hs);
//    layoutKey->addWidget(pbOd);
    layoutKey->addItem(hs0);
    layoutKey->addWidget(pbMeasure);
    layoutKey->addItem(hs1);
    layoutKey->addWidget(pbAutoFreeze);
    layoutKey->addWidget(pbAuto);
    layoutKey->addWidget(pbManual);
    layoutKey->addItem(hs2);
    layoutKey->addWidget(pbContact);
    layoutKey->addWidget(pbImmersion);
    layoutKey->addItem(hs3);
    layoutKey->addWidget(pbCataract);
    layoutKey->addWidget(pbAphakic);
    layoutKey->addItem(hs4);

    connect(pbAuto, SIGNAL(clicked()), SLOT(keyAutoClicked()));
}

void key::keyAutoClicked()
{
    emit keyAuto();
}


