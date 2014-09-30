#include "key_radio.h"

key_radio::key_radio(QWidget *parent) :
    QWidget(parent)
{
    curentParam = CurentParam::instanse();
    //----------------------------------------- Button
    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);

    QGroupBox    *gbAuto = new QGroupBox();
    QHBoxLayout  *ltAuto = new QHBoxLayout(gbAuto);
    QRadioButton *rbAutoFreeze = new QRadioButton(tr("Auto Freeze"));
    QRadioButton *rbAuto = new QRadioButton(tr("Auto"));
    QRadioButton *rbManual = new QRadioButton(tr("Manual"));
    rbManual->setChecked(true);
    ltAuto->addWidget(rbAutoFreeze);
    ltAuto->addWidget(rbAuto);
    ltAuto->addWidget(rbManual);

    QSpacerItem  *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbContact = new QGroupBox();
    QHBoxLayout  *ltContact = new QHBoxLayout(gbContact);
    QRadioButton *rbContact = new QRadioButton(tr("Contact"));
    QRadioButton *rbImmersion = new QRadioButton(tr("Immersion"));
    rbContact->setChecked(true);
    ltContact->addWidget(rbContact);
    ltContact->addWidget(rbImmersion);


    QSpacerItem  *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbCataract = new QGroupBox();
    QHBoxLayout  *ltCataract = new QHBoxLayout(gbCataract);
    QRadioButton *rbCataract = new QRadioButton(tr("Cataract"));
    QRadioButton *rbAphakic = new QRadioButton(tr("Aphakic"));
    rbCataract->setObjectName("rbCataract");
    rbAphakic->setObjectName("rbAphakic");
    rbAphakic->setChecked(true);
    ltCataract->addWidget(rbCataract);
    ltCataract->addWidget(rbAphakic);


    QSpacerItem  *hs4 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gbEye = new QGroupBox();
    QHBoxLayout  *ltEye = new QHBoxLayout(gbEye);
    rbOd = new QRadioButton(tr("OD"));
    rbOs = new QRadioButton(tr("OS"));
    rbOd->setChecked(true);
    ltEye->addWidget(rbOd);
    ltEye->addWidget(rbOs);

//    QSpacerItem *hs5 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutkey_radio->setSpacing(0);
    layoutkey_radio->addWidget(gbAuto);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(gbContact);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(gbCataract);
    layoutkey_radio->addItem(hs4);
    layoutkey_radio->addWidget(gbEye);

    connect(rbAphakic,  SIGNAL(clicked(bool)), SLOT(doChangeCataract()));
    connect(rbCataract, SIGNAL(clicked(bool)), SLOT(doChangeCataract()));
    connect(rbOd, SIGNAL(clicked(bool)), SLOT(doChangeSide()));
    connect(rbOs, SIGNAL(clicked(bool)), SLOT(doChangeSide()));
    connect(curentParam, SIGNAL(changeSideSignal()), SLOT(changeSideSlot()));
}

void key_radio::changeSideSlot()
{
    if(curentParam->sideOD)
        rbOd->setChecked(true);
    else
        rbOs->setChecked(true);
}

void key_radio::doChangeSide()
{
    curentParam->sideOD = rbOd->isChecked();
    curentParam->refreshPatientModel();
}

void key_radio::doChangeCataract()
{
    qDebug()<<(QObject::sender()->objectName()=="rbAphakic");
    emit changeCataractSignal((QObject::sender()->objectName()=="rbAphakic"));
}
