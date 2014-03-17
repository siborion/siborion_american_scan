#include "key_radio.h"

key_radio::key_radio(QWidget *parent) :
    QWidget(parent)
{
    //----------------------------------------- Button
    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);

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

    layoutkey_radio->setSpacing(0);
//    layoutkey_radio->addItem(hs);
//    layoutkey_radio->addWidget(pbOd);
    layoutkey_radio->addItem(hs0);
    layoutkey_radio->addWidget(pbMeasure);
    layoutkey_radio->addItem(hs1);
    layoutkey_radio->addWidget(pbAutoFreeze);
    layoutkey_radio->addWidget(pbAuto);
    layoutkey_radio->addWidget(pbManual);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(pbContact);
    layoutkey_radio->addWidget(pbImmersion);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(pbCataract);
    layoutkey_radio->addWidget(pbAphakic);
    layoutkey_radio->addItem(hs4);

    connect(pbAuto, SIGNAL(clicked()), SLOT(key_radioAutoClicked()));
}

void key_radio::key_radioAutoClicked()
{
    emit key_radioAuto();
}


