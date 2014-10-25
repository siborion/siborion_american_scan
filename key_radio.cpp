#include "key_radio.h"

key_radio::key_radio(QWidget *parent) :
    QWidget(parent)
{
    curentParam = CurentParam::instanse();
    //----------------------------------------- Button
    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);

    QGroupBox    *gbAuto = new QGroupBox();
    QHBoxLayout  *ltAuto = new QHBoxLayout(gbAuto);
    rbAutoFreeze = new QRadioButton(tr("Auto Freeze"));
    rbAuto       = new QRadioButton(tr("Auto"));
    rbManual     = new QRadioButton(tr("Manual"));
    rbAutoFreeze->setObjectName("AutoFreeze");
    rbAuto->setObjectName      ("Auto");
    rbManual->setObjectName    ("Manual");

    rbAutoFreeze->setChecked(true);
    curentParam->workRegim =  curentParam->WorkRegim::regimAutoFreez;
//    emit changeCataractSignal(true);
    ltAuto->addWidget(rbAutoFreeze);
    ltAuto->addWidget(rbAuto);
    ltAuto->addWidget(rbManual);

    QSpacerItem  *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbContact = new QGroupBox();
    QHBoxLayout  *ltContact = new QHBoxLayout(gbContact);
    rbContact = new QRadioButton(tr("Contact"));
    rbImmersion = new QRadioButton(tr("Immersion"));
    rbContact->setObjectName("Contact");
    rbImmersion->setObjectName("Immersion");
    rbContact->setChecked(true);
    ltContact->addWidget(rbContact);
    ltContact->addWidget(rbImmersion);


    QSpacerItem  *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbCataract = new QGroupBox();
    QHBoxLayout  *ltCataract = new QHBoxLayout(gbCataract);
    rbCataract = new QRadioButton(tr("Cataract"));
    rbAphakic = new QRadioButton(tr("Aphakic"));
    rbCataract->setObjectName("Cataract");
    rbAphakic->setObjectName("Aphakic");
    rbCataract->setChecked(true);
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

    regimMeasure  = RegimMeasure::AUTOFREEZ;
    regimContact  = RegimContact::CONTACT;
    regimCataract = RegimCataract::CATARACT;
    regimSide     = RegimSide::OD;
    refresh();


    connect(gbAuto, SIGNAL(toggled(bool))   , SLOT(doChangeRegim()));

//    connect(rbAutoFreeze,  SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
//    connect(rbAuto,        SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
//    connect(rbManual,      SIGNAL(clicked(bool)), SLOT(doChangeRegim()));

//    connect(rbAphakic,  SIGNAL(clicked(bool)), SLOT(doChangeCataract()));
//    connect(rbCataract, SIGNAL(clicked(bool)), SLOT(doChangeCataract()));

//    connect(rbImmersion, SIGNAL(clicked(bool)), SLOT(doChangeContact()));
//    connect(rbContact,   SIGNAL(clicked(bool)), SLOT(doChangeContact()));

//    connect(rbOd, SIGNAL(clicked(bool)), SLOT(doChangeSide()));
//    connect(rbOs, SIGNAL(clicked(bool)), SLOT(doChangeSide()));
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
    emit changeCataractSignal((QObject::sender()->objectName()=="Cataract"));
}

void key_radio::doChangeContact()
{
    emit changeContactSignal((QObject::sender()->objectName()=="Contact"));
}

void key_radio::refresh()
{
    if(regimMeasure  == RegimMeasure::AUTOFREEZ)
        rbAutoFreeze->setChecked(true);

    if(regimMeasure  == RegimMeasure::AUTO)
        rbAuto->setChecked(true);

    if(regimMeasure == RegimMeasure::MANUAL)
        rbManual->setChecked(true);

    if(regimContact  == RegimContact::CONTACT)
        rbContact->setChecked(true);

    if(regimContact  == RegimContact::IMMERSION)
        rbImmersion->setChecked(true);

    if(regimCataract == RegimCataract::CATARACT)
        rbCataract->setChecked(true);

    if(regimCataract == RegimCataract::APHAKIC)
        rbAphakic->setChecked(true);

    if(regimSide     == RegimSide::OD)
        rbOd->setChecked(true);

    if(regimSide     == RegimSide::OS)
        rbOs->setChecked(true);
}

void key_radio::doChangeRegim()
{
    if(rbAutoFreeze->isChecked())
        regimMeasure  = RegimMeasure::AUTOFREEZ;
    if(rbAuto->isChecked())
        regimMeasure  = RegimMeasure::AUTO;
    if(rbManual->isChecked())
        regimMeasure  = RegimMeasure::MANUAL;

    if(rbContact->isChecked())
        regimContact  = RegimContact::CONTACT;
    if(rbImmersion->isChecked())
        regimContact  = RegimContact::IMMERSION;

    if(rbCataract->isChecked())
        regimCataract = RegimCataract::CATARACT;
    if(rbAphakic->isChecked())
        regimCataract = RegimCataract::APHAKIC;

    if(rbOd->isChecked())
        regimSide     = RegimSide::OD;
    if(rbOs->isChecked())
        regimSide     = RegimSide::OS;

    qDebug()<<regimMeasure;

//    if (QObject::sender()->objectName()=="AutoFreeze")
//        curentParam->workRegim =  curentParam->WorkRegim::regimAutoFreez;

//    if (QObject::sender()->objectName()=="Auto")
//        curentParam->workRegim =  curentParam->WorkRegim::regimAuto;

//    if (QObject::sender()->objectName()=="Manual")
//        curentParam->workRegim =  curentParam->WorkRegim::regimManual;

//    emit changeCataractSignal(!(QObject::sender()->objectName()=="Manual"));

}


