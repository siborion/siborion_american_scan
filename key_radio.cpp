#include "key_radio.h"
#include <QDebug>

key_radio::key_radio(QWidget *parent, CurParam *link) :
    QWidget(parent)
{

    setContentsMargins(-1, 0, -1, 0);

    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);
    layoutkey_radio->setContentsMargins(-1, 2, -1, 2);

    curentParam = link;

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
    rbManual->setObjectName("rbManual");
    rbAuto->setObjectName("rbAuto");
    rbAutoFreeze->setObjectName("rbAutoFreeze");
    rbAutoFreeze->setChecked(true);
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
    rbOd->setObjectName("rbOD");
    rbOs->setObjectName("rbOS");
    rbOd->setFont(font);
    rbOs->setFont(font);
    rbOd->setChecked(true);

    ltEye->addWidget(rbOd);
    ltEye->addWidget(rbOs);

    QSpacerItem  *hs5 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutkey_radio->setSpacing(0);
    layoutkey_radio->addWidget(gbAuto);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(gbContact);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(gbCataract);
    layoutkey_radio->addItem(hs4);
    layoutkey_radio->addWidget(gbEye);
    layoutkey_radio->addItem(hs5);

//    curentParam->regimMeasure  = REGIM::AUTOFREEZ;
//    curentParam->regimContact  = REGIM::CONTACT;
//    curentParam->regimCataract = REGIM::CATARACT;
//    curentParam->regimSide     = REGIM::OD;

    connect(rbAutoFreeze,  SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbAuto,        SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbManual,      SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbAphakic,     SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbCataract,    SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbImmersion,   SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbContact,     SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbOd,          SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
    connect(rbOs,          SIGNAL(clicked(bool)), SLOT(doChangeRegim()));
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
    if(curentParam->regimMeasure  == REGIM::AUTOFREEZ)
        rbAutoFreeze->setChecked(true);
    if(curentParam->regimMeasure  == REGIM::AUTO)
        rbAuto->setChecked(true);
    if(curentParam->regimMeasure == REGIM::MANUAL)
        rbManual->setChecked(true);
    if(curentParam->regimContact  == REGIM::CONTACT)
        rbContact->setChecked(true);
    if(curentParam->regimContact  == REGIM::IMMERSION)
        rbImmersion->setChecked(true);
    if(curentParam->regimCataract == REGIM::CATARACT)
        rbCataract->setChecked(true);
    if(curentParam->regimCataract == REGIM::APHAKIC)
        rbAphakic->setChecked(true);
    if(curentParam->regimSide     == REGIM::OD)
        rbOd->setChecked(true);
    if(curentParam->regimSide     == REGIM::OS)
        rbOs->setChecked(true);
}

void key_radio::doChangeRegim()
{
    emit changeInterval(QObject::sender()->objectName());

    if(rbAutoFreeze->isChecked())
        curentParam->regimMeasure  = REGIM::AUTOFREEZ;
    if(rbAuto->isChecked())
        curentParam->regimMeasure  = REGIM::AUTO;
    if(rbManual->isChecked())
        curentParam->regimMeasure  = REGIM::MANUAL;
    if(rbContact->isChecked())
        curentParam->regimContact  = REGIM::CONTACT;
    if(rbImmersion->isChecked())
        curentParam->regimContact  = REGIM::IMMERSION;
    if(rbCataract->isChecked())
        curentParam->regimCataract = REGIM::CATARACT;
    if(rbAphakic->isChecked())
        curentParam->regimCataract = REGIM::APHAKIC;
    if(rbOd->isChecked())
        curentParam->regimSide     = REGIM::OD;
    if(rbOs->isChecked())
        curentParam->regimSide     = REGIM::OS;

    emit changeInterval(QObject::sender()->objectName());
}

void key_radio::changeSideCalculatorSlot()
{
    if(curentParam->regimSide == REGIM::OD)
    {
        rbOd->setChecked(true);
        emit rbOd->clicked(true);
    }
    else
    {
        rbOs->setChecked(true);
        emit rbOs->clicked(true);
    }
}
