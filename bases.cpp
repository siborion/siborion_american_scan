#include "bases.h"

bases::bases(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();

    QHBoxLayout *Layout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QHBoxLayout *topRightLayout  = new QHBoxLayout();
    QHBoxLayout *botRightLayout  = new QHBoxLayout();

    QGroupBox *gbSelect = new QGroupBox();
    QHBoxLayout *groupBoxLayout  = new QHBoxLayout(gbSelect);
    QRadioButton *rbPatient = new QRadioButton(tr("Patient"), gbSelect);
    rbPatient->setChecked(true);
    QRadioButton *rbDoctor  = new QRadioButton(tr("Doctor"), gbSelect);
    QRadioButton *rbLens    = new QRadioButton(tr("Lens Styles"), gbSelect);
    groupBoxLayout->addWidget(rbPatient);
    groupBoxLayout->addWidget(rbDoctor);
    groupBoxLayout->addWidget(rbLens);

    QLabel    *lSearch  = new QLabel(tr("Search"));
    QLineEdit *leSearch = new QLineEdit();

    model = new QSqlQueryModel ();
    pTest = new QPushButton();
    pbAdd = new QPushButton();
    pbEdit = new QPushButton();
    pbDel = new QPushButton();
    pbPatientHistory = new QPushButton();

    twTable = new adjview();
    twTable->setModel(model);
    twTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    topRightLayout->addWidget(gbSelect);
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

    adjTable(BaseType::enPatient);

    connect(rbPatient, SIGNAL(clicked(bool)), SLOT(changeBasePatient(bool)));
    connect(rbDoctor, SIGNAL(clicked(bool)), SLOT(changeBaseDoctor(bool)));
    connect(rbLens, SIGNAL(clicked(bool)), SLOT(changeBaseLens(bool)));
    connect(pbAdd,  SIGNAL(pressed()), SLOT(Add()));
    connect(pbEdit, SIGNAL(pressed()), SLOT(Edit()));
}

void bases::adjTable(BaseType::Status Val)
{
    QString str;
    QStringList lst;
    QStringList lstButton;
    QList<int>  columnPercent;

    columnPercent.clear();
    TypeBase = Val;
    switch (TypeBase)
    {
    case BaseType::enPatient:
        columnPercent<<10   <<   10        <<      20        <<      20       <<       20        <<     20;
        lst<<tr("Ref.№")<<tr("Patient ID")<<tr("First Name")<<tr("Last Name")<<tr("Doctor Name")<<tr("Notes");
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient")<<tr("Patient History");
        str = "SELECT  ref, id, first, last, doctor, notes from v_patient;";
        break;
    case BaseType::enDoctor:
        columnPercent   <<       10        <<      30        <<      30       <<     30;
        lst             <<tr("Doctor Id") <<tr("First Name")<<tr("Last Name")<<tr("Notes");
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        str = "SELECT id from doctor;";
        break;
    case BaseType::enLens:
        columnPercent   <<       10       <<      20      <<      20         <<     20    <<      20    <<      10;
        lst             <<tr("Lens Name")<<tr("Mfg Name")<<tr("Mfg A_Const")<<tr("Mfg ACD")<<tr("Mfg SF")<<tr("Hoffer ACD");
        lstButton<<tr("Add Lens")<<tr("Edit Lens")<<tr("Delete Lens");
        str = "SELECT id from lens;";
        break;
    }
    model->setQuery(str);
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
    fillModelHead(lst);
}

void bases::changeBasePatient(bool Val)
{
    if(Val)
        adjTable(BaseType::enPatient);
}
void bases::changeBaseDoctor(bool Val)
{
    if(Val)
        adjTable(BaseType::enDoctor);
}
void bases::changeBaseLens(bool Val)
{
    if(Val)
        adjTable(BaseType::enLens);
}

void bases::Add()
{
    if(TypeBase==BaseType::enPatient)
    {
        patient *pPatient = new patient(0);
        if(pPatient->exec() == QDialog::Accepted)
        {

        }
        delete pPatient;
    }
    if(TypeBase==BaseType::enDoctor)
    {
        doctor *pDoctor = new doctor();
        if(pDoctor->exec() == QDialog::Accepted)
        {
//            qDebug() << pDoctor->modelDoctor->item(0,1)->text();
        }
        delete pDoctor;
    }
    if(TypeBase==BaseType::enLens)
    {
        lens *pLens = new lens();
        if(pLens->exec() == QDialog::Accepted)
        {

        }
        delete pLens;
    }
}

void bases::Edit()
{
    quint32 curRow;
    curRow = twTable->currentIndex().row();

    if(TypeBase==BaseType::enPatient)
    {
        patient *pPatient = new patient(model->data(model->index(curRow, 1)).toUInt());
        if(pPatient->exec() == QDialog::Accepted)
        {
        }
    }

}

void bases::Del()
{
    switch (TypeBase)
    {
    case BaseType::enPatient:
        break;
    case BaseType::enDoctor:
        break;
    case BaseType::enLens:
        break;
    }
}

void bases::fillModelHead(QStringList sl)
{
    for(int i=0; i<sl.count(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, sl.at(i), Qt::DisplayRole);
    }

//    QSqlQuery sqData;
//    switch (TypeBase)
//    {
//    case BaseType::enPatient:
//        sqData = pBase->getData("select * from patient;");
//      break;
//    case BaseType::enDoctor:
//        sqData = pBase->getData("select * from patient;");
//        break;
//    case BaseType::enLens:
//        sqData = pBase->getData("select * from patient;");
//        break;
//    }
//    model->setHeaderData(0, Qt::Horizontal, "454545", Qt::DisplayRole);
//    model->setQuery("select id from patient;");
//    qDebug() << model->lastError();
}




