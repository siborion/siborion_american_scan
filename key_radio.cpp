#include "key_radio.h"

key_radio::key_radio(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);


    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    font.setFamily(QStringLiteral("Arial"));

    QGroupBox    *gbAuto = new QGroupBox();
    QHBoxLayout  *ltAuto = new QHBoxLayout(gbAuto);
    rbAutoFreeze = new QRadioButton(tr("Auto Freeze"));
    rbAuto       = new QRadioButton(tr("Auto"));
    rbManual     = new QRadioButton(tr("Manual"));
    rbAutoFreeze->setObjectName("AutoFreeze");
    rbAuto->setObjectName      ("Auto");
    rbManual->setObjectName    ("Manual");
    rbAutoFreeze->setFont(font);
    rbAuto->setFont(font);
    rbManual->setFont(font);

    ltAuto->addWidget(rbAutoFreeze);
    ltAuto->addWidget(rbAuto);
    ltAuto->addWidget(rbManual);
    rbAutoFreeze->setChecked(true);

    QSpacerItem  *hs2 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbContact = new QGroupBox();
    QHBoxLayout  *ltContact = new QHBoxLayout(gbContact);
    rbContact = new QRadioButton(tr("Contact"));
    rbImmersion = new QRadioButton(tr("Immersion"));
    rbContact->setObjectName("Contact");
    rbImmersion->setObjectName("Immersion");
    ltContact->addWidget(rbContact);
    ltContact->addWidget(rbImmersion);
    rbContact->setFont(font);
    rbImmersion->setFont(font);
    rbContact->setChecked(true);

    QSpacerItem  *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QGroupBox    *gbCataract = new QGroupBox();
    QHBoxLayout  *ltCataract = new QHBoxLayout(gbCataract);
    rbCataract = new QRadioButton(tr("Cataract"));
    rbAphakic = new QRadioButton(tr("Aphakic"));
    rbCataract->setObjectName("Cataract");
    rbAphakic->setObjectName("Aphakic");
    ltCataract->addWidget(rbCataract);
    ltCataract->addWidget(rbAphakic);
    rbCataract->setFont(font);
    rbAphakic->setFont(font);
    rbCataract->setChecked(true);


    QSpacerItem  *hs4 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gbEye = new QGroupBox();
    QHBoxLayout  *ltEye = new QHBoxLayout(gbEye);
    rbOd = new QRadioButton(tr("OD"));
    rbOs = new QRadioButton(tr("OS"));
    rbOd->setObjectName("OD");
    rbOs->setObjectName("OS");
    rbOd->setFont(font);
    rbOs->setFont(font);
    rbOd->setChecked(true);

    ltEye->addWidget(rbOd);
    ltEye->addWidget(rbOs);

//    QSpacerItem  *hs5 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutkey_radio->setSpacing(0);
    layoutkey_radio->addWidget(gbAuto);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(gbContact);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(gbCataract);
    layoutkey_radio->addItem(hs4);
    layoutkey_radio->addWidget(gbEye);
//    layoutkey_radio->addItem(hs5);

//    curentParam->regimMeasure  = RegimMeasure::AUTOFREEZ;
//    curentParam->regimContact  = RegimContact::CONTACT;
//    curentParam->regimCataract = RegimCataract::CATARACT;
//    curentParam->regimSide     = RegimSide::OD;
//    refresh();
//    emit change();
//    doChangeRegim();

    connect(rbAutoFreeze,  SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbAuto,        SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbManual,      SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbAphakic,  SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbCataract, SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbImmersion, SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbContact,   SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbOd, SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbOs, SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
//    connect(curentParam, SIGNAL(changeSideSignal()), SLOT(changeSideSlot()));
}

void key_radio::changeSideSlot()
{
//    if(curentParam->regimSide == RegimSide::OD)
//        rbOd->setChecked(true);
//    else
//        rbOs->setChecked(true);
}

void key_radio::refresh()
{
//    if(curentParam->regimMeasure  == RegimMeasure::AUTOFREEZ)
//        rbAutoFreeze->setChecked(true);
//    if(curentParam->regimMeasure  == RegimMeasure::AUTO)
//        rbAuto->setChecked(true);
//    if(curentParam->regimMeasure == RegimMeasure::MANUAL)
//        rbManual->setChecked(true);
//    if(curentParam->regimContact  == RegimContact::CONTACT)
//        rbContact->setChecked(true);
//    if(curentParam->regimContact  == RegimContact::IMMERSION)
//        rbImmersion->setChecked(true);
//    if(curentParam->regimCataract == RegimCataract::CATARACT)
//        rbCataract->setChecked(true);
//    if(curentParam->regimCataract == RegimCataract::APHAKIC)
//        rbAphakic->setChecked(true);
//    if(curentParam->regimSide     == RegimSide::OD)
//        rbOd->setChecked(true);
//    if(curentParam->regimSide     == RegimSide::OS)
//        rbOs->setChecked(true);
}

void key_radio::doChangeRegim()
{
//    if(rbAutoFreeze->isChecked())
//        curentParam->regimMeasure  = RegimMeasure::AUTOFREEZ;
//    if(rbAuto->isChecked())
//        curentParam->regimMeasure  = RegimMeasure::AUTO;
//    if(rbManual->isChecked())
//        curentParam->regimMeasure  = RegimMeasure::MANUAL;
//    if(rbContact->isChecked())
//        curentParam->regimContact  = RegimContact::CONTACT;
//    if(rbImmersion->isChecked())
//        curentParam->regimContact  = RegimContact::IMMERSION;
//    if(rbCataract->isChecked())
//        curentParam->regimCataract = RegimCataract::CATARACT;
//    if(rbAphakic->isChecked())
//        curentParam->regimCataract = RegimCataract::APHAKIC;
//    if(rbOd->isChecked())
//        curentParam->regimSide     = RegimSide::OD;
//    if(rbOs->isChecked())
//        curentParam->regimSide     = RegimSide::OS;
//    if ((QObject::sender()->objectName()=="OD")||(QObject::sender()->objectName()=="OS"))
//        curentParam->refreshPatientModel();
//    emit change();
}
