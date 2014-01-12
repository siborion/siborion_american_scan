#include "bases.h"

bases::bases(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *Layout = new QHBoxLayout(this);

    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QHBoxLayout *topRightLayout  = new QHBoxLayout();
    QHBoxLayout *botRightLayout  = new QHBoxLayout();

    QSpacerItem *buttonSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QPushButton *pbPatient = new QPushButton(tr("Patient"));
    QPushButton *pbDoctor = new QPushButton(tr("Doctor"));
    QPushButton *pbLens = new QPushButton(tr("Lens Styles"));
    pbPatient->setMinimumHeight(50);
    pbDoctor->setMinimumHeight(50);
    pbLens->setMinimumHeight(50);
    QSpacerItem *buttonSpacerBot = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    leftLayout->addItem(buttonSpacerTop);
    leftLayout->addWidget(pbPatient);
    leftLayout->addWidget(pbDoctor);
    leftLayout->addWidget(pbLens);
    leftLayout->addItem(buttonSpacerBot);

    QLabel    *lSearch  = new QLabel(tr("Search"));
    QLineEdit *leSearch = new QLineEdit();

    model = new QStandardItemModel();
    pbAdd = new QPushButton();
    pbEdit = new QPushButton();
    pbDel = new QPushButton();
    pbPatientHistory = new QPushButton();

    twTable = new adjview();
    twTable->setModel(model);

    topRightLayout->addWidget(lSearch);
    topRightLayout->addWidget(leSearch);

    botRightLayout->addWidget(pbAdd);
    botRightLayout->addWidget(pbEdit);
    botRightLayout->addWidget(pbDel);
    botRightLayout->addWidget(pbPatientHistory);

    rightLayout->addLayout(topRightLayout, 0, 0);
    rightLayout->addWidget(twTable,        1, 0, 1, 1);
    rightLayout->addLayout(botRightLayout, 2, 0);

    Layout->addLayout(leftLayout);
    Layout->addLayout(rightLayout);

    adjTable(enPatient);

    connect(pbPatient, SIGNAL(pressed()), SLOT(changeBasePatient()));
    connect(pbDoctor, SIGNAL(pressed()), SLOT(changeBaseDoctor()));
    connect(pbLens, SIGNAL(pressed()), SLOT(changeBaseLens()));

    connect(pbAdd,  SIGNAL(pressed()), SLOT(Add()));
    connect(pbEdit, SIGNAL(pressed()), SLOT(Add()));
}

void bases::adjTable(quint8 Val)
{
    QStringList lst;
    QStringList lstButton;
    QList<int>  columnPercent;

    columnPercent.clear();
    TypeBase = Val;
    switch (TypeBase)
    {
    case enPatient:
        columnPercent   <<       5        <<      20        <<      20       <<       20        <<     35;
        lst<<tr("Ref.№")<<tr("Patient ID")<<tr("First Name")<<tr("Last Name")<<tr("Doctor Name")<<tr("Notes");
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient")<<tr("Patient History");
        break;
    case enDoctor:
        columnPercent   <<       5        <<      30        <<      30       <<     35;
        lst             <<tr("Doctor Id") <<tr("First Name")<<tr("Last Name")<<tr("Notes");
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        break;
    case enLens:
        columnPercent   <<       5       <<      20      <<      20         <<     20    <<      20    <<      15;
        lst             <<tr("Lens Name")<<tr("Mfg Name")<<tr("Mfg A_Const")<<tr("Mfg ACD")<<tr("Mfg SF")<<tr("Hoffer ACD");
        lstButton<<tr("Add Lens")<<tr("Edit Lens")<<tr("Delete Lens");
        break;
    }
    model->setColumnCount(lst.count());
    model->setHorizontalHeaderLabels(lst);
    pbAdd->setText (lstButton.at(0));
    pbEdit->setText(lstButton.at(1));
    pbDel->setText (lstButton.at(2));
    if(lstButton.count()>3)
    {
        pbPatientHistory->setVisible(true);
        pbPatientHistory->setText(lstButton.at(3));
    }
    else
        pbPatientHistory->setVisible(false);
    twTable->setColumnPercent(columnPercent);
}

void bases::changeBasePatient()
{
    adjTable(enPatient);
}
void bases::changeBaseDoctor()
{
    adjTable(enDoctor);
}
void bases::changeBaseLens()
{
    adjTable(enLens);
}


void bases::Add()
{
    if(TypeBase==enPatient)
    {
        patient *pPatient = new patient();
        if(pPatient->exec() == QDialog::Accepted)
        {

        }
        delete pPatient;
    }
    if(TypeBase==enDoctor)
    {
        doctor *pDoctor = new doctor();
        if(pDoctor->exec() == QDialog::Accepted)
        {
            qDebug() << pDoctor->modelDoctor->item(0,1)->text();
        }
        delete pDoctor;
    }
    if(TypeBase==enLens)
    {
        lens *pLens = new lens();
        if(pLens->exec() == QDialog::Accepted)
        {

        }
        delete pLens;
    }

//    switch (TypeBase)
//    {
//    case enPatient:
//        patient *pPatient = new patient();
//        break;
//    case enDoctor:
//        patient *pPatient1 = new patient();
//        break;
//    case enLens:
//        patient *pPatient2 = new patient();
//        break;
//    }
}

void bases::Edit()
{
    switch (TypeBase)
    {
    case enPatient:
        break;
    case enDoctor:
        break;
    case enLens:
        break;
    }
}

void bases::Del()
{
    switch (TypeBase)
    {
    case enPatient:
        break;
    case enDoctor:
        break;
    case enLens:
        break;
    }
}
