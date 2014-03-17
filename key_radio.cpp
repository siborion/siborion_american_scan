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

    QGroupBox    *gbAuto = new QGroupBox();
    QHBoxLayout  *ltAuto = new QHBoxLayout(gbAuto);
    QRadioButton *rbAutoFreeze = new QRadioButton(tr("Auto Freeze"));
    QRadioButton *rbAuto = new QRadioButton(tr("Auto"));
    QRadioButton *rbManual = new QRadioButton(tr("Manual"));
    ltAuto->addWidget(rbAutoFreeze);
    ltAuto->addWidget(rbAuto);
    ltAuto->addWidget(rbManual);

    QSpacerItem  *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbContact = new QGroupBox();
    QHBoxLayout  *ltContact = new QHBoxLayout(gbContact);
    QRadioButton *rbContact = new QRadioButton(tr("Contact"));
    QRadioButton *rbImmersion = new QRadioButton(tr("Immersion"));
    ltContact->addWidget(rbContact);
    ltContact->addWidget(rbImmersion);


    QSpacerItem  *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbCataract = new QGroupBox();
    QHBoxLayout  *ltCataract = new QHBoxLayout(gbCataract);
    QRadioButton *rbCataract = new QRadioButton(tr("Cataract"));
    QRadioButton *rbAphakic = new QRadioButton(tr("Aphakic"));
    ltCataract->addWidget(rbCataract);
    ltCataract->addWidget(rbAphakic);



//    QSpacerItem *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    QPushButton *pbCataract = new QPushButton(tr("Cataract"));
//    QPushButton *pbAphakic = new QPushButton(tr("Aphakic"));
    QSpacerItem *hs4 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutkey_radio->setSpacing(0);
//    layoutkey_radio->addItem(hs);
//    layoutkey_radio->addWidget(pbOd);
    layoutkey_radio->addItem(hs0);
    layoutkey_radio->addWidget(pbMeasure);
    layoutkey_radio->addItem(hs1);
    layoutkey_radio->addWidget(gbAuto);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(gbContact);
//    layoutkey_radio->addWidget(pbContact);
//    layoutkey_radio->addWidget(pbImmersion);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(gbCataract);
//    layoutkey_radio->addWidget(pbCataract);
//    layoutkey_radio->addWidget(pbAphakic);
    layoutkey_radio->addItem(hs4);

    connect(pbMeasure, SIGNAL(clicked()), SLOT(key_radioAutoClicked()));
}

void key_radio::key_radioAutoClicked()
{
    emit keyAuto();
}


