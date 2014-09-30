#include "key_radio.h"

key_radio::key_radio(QWidget *parent) :
    QWidget(parent)
{
    curentParam = CurentParam::instanse();
    //----------------------------------------- Button
    QHBoxLayout *layoutkey_radio = new QHBoxLayout(this);

//    QSpacerItem *hs = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    QPushButton *pbOd = new QPushButton(tr("OD"));
//    QSpacerItem *hs0 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    QPushButton *pbSave = new QPushButton(tr("Save"));
//    QPushButton *pbMeasure = new QPushButton(tr("Measure"));
//    QSpacerItem *hs1 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

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



//    QSpacerItem *hs3 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    QPushButton *pbCataract = new QPushButton(tr("Cataract"));
//    QPushButton *pbAphakic = new QPushButton(tr("Aphakic"));
    QSpacerItem *hs5 = new QSpacerItem(50, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layoutkey_radio->setSpacing(0);
//    layoutkey_radio->addItem(hs);
//    layoutkey_radio->addWidget(pbOd);
//    layoutkey_radio->addItem(hs0);
//    layoutkey_radio->addWidget(pbMeasure);
//    layoutkey_radio->addItem(hs1);
    layoutkey_radio->addWidget(gbAuto);
    layoutkey_radio->addItem(hs2);
    layoutkey_radio->addWidget(gbContact);
//    layoutkey_radio->addWidget(pbContact);
//    layoutkey_radio->addWidget(pbImmersion);
    layoutkey_radio->addItem(hs3);
    layoutkey_radio->addWidget(gbCataract);
    layoutkey_radio->addItem(hs4);
    layoutkey_radio->addWidget(gbEye);
//    layoutkey_radio->addWidget(pbCataract);
//    layoutkey_radio->addWidget(pbAphakic);
//    layoutkey_radio->addItem(hs4);
//    layoutkey_radio->addWidget(pbSave);


//    rbOs->setChecked(true);

 //   connect(pbMeasure, SIGNAL(clicked()), SLOT(key_radioAutoClicked()));
 //   connect(pbSave, SIGNAL(clicked()), SLOT(key_radioSaveClicked()));
//    connect(rbOd, SIGNAL(clicked(bool)), SLOT(key_radioOd(bool)));
//    connect(rbOs, SIGNAL(clicked(bool)), SLOT(key_radioOs(bool)));

    connect(rbOd, SIGNAL(clicked(bool)), SLOT(changeSideSlot()));
    connect(curentParam, SIGNAL(changeSideSignal()), SLOT(changeSideSlot()));
}

void key_radio::changeSideSlot()
{
    if(curentParam->sideOD)
        rbOd->setChecked(true);
    else
        rbOs->setChecked(true);
    qDebug()<<"8888888888888888";
}

//void key_radio::key_radioAutoClicked()
//{
//    emit keyAuto();
//}

//void key_radio::key_radioOd(bool val)
//{
//    emit changeEye((quint8)0);
//}

//void key_radio::key_radioOs(bool val)
//{
//   emit changeEye((quint8)1);
//}



