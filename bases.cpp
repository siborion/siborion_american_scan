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
    QRadioButton *rbPatient = new QRadioButton(tr(""), gbSelect);
    rbPatient->setChecked(true);
    QRadioButton *rbDoctor  = new QRadioButton(tr(""), gbSelect);
    QRadioButton *rbLens    = new QRadioButton(tr("Lens Styles"), gbSelect);
    groupBoxLayout->addWidget(rbPatient);
    groupBoxLayout->addWidget(rbDoctor);
    groupBoxLayout->addWidget(rbLens);

    QIcon iconPatient;
    iconPatient.addFile(QStringLiteral(":/test/patient"), QSize(), QIcon::Normal, QIcon::Off);
    rbPatient->setIcon(iconPatient);
    rbPatient->setIconSize(QSize(80, 80));

    QIcon iconDoctor;
    iconDoctor.addFile(QStringLiteral(":/test/doctor"), QSize(), QIcon::Normal, QIcon::Off);
    rbDoctor->setIcon(iconDoctor);
    rbDoctor->setIconSize(QSize(80, 80));

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

    if(model->rowCount()>0)
    {
        twTable->setCurrentIndex(model->index(0,0));
        qDebug()<<model->index(0,0);
    }
    qDebug()<<model->rowCount();


    connect(rbPatient, SIGNAL(clicked(bool)), SLOT(changeBasePatient(bool)));
    connect(rbDoctor, SIGNAL(clicked(bool)), SLOT(changeBaseDoctor(bool)));
    connect(rbLens, SIGNAL(clicked(bool)), SLOT(changeBaseLens(bool)));
    connect(pbAdd,  SIGNAL(pressed()), SLOT(Add()));
    connect(pbEdit, SIGNAL(pressed()), SLOT(Edit()));
    connect(pbDel, SIGNAL(pressed()), SLOT(Del()));
//    connect(twTable, SIGNAL(clicked(QModelIndex)), SLOT(DelIndex(QModelIndex)));
    connect(twTable, SIGNAL(doubleClicked(QModelIndex)), SLOT(EditIndex(QModelIndex)));
    connect(twTable->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex,QModelIndex)));
    qDebug()<<twTable->selectionModel();

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
        str = "SELECT  ref, id, name, last, doctor, notes from v_patient;";
        break;
    case BaseType::enDoctor:
        columnPercent   <<       10        <<      30        <<      30       <<     30;
        lst             <<tr("Doctor Id") <<tr("First Name")<<tr("Last Name")<<tr("Notes");
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        str = "SELECT id, name, last, note from doctor;";
        break;
    case BaseType::enLens:
        columnPercent   << 0 <<            10       <<      20      <<      20         <<     20    <<      20    <<      10;
        lst             <<tr("id") <<tr("Lens Name")<<tr("Mfg Name")<<tr("Mfg A_Const")<<tr("Mfg ACD")<<tr("Mfg SF")<<tr("Hoffer ACD");
        lstButton<<tr("Add Lens")<<tr("Edit Lens")<<tr("Delete Lens");
        str = "SELECT id, name, mfg, aconst, acd, sf, hacd from lens;";
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
            adjTable(BaseType::enPatient);
        }
        delete pPatient;
    }
    if(TypeBase==BaseType::enDoctor)
    {
        dialog_doctor *pDoctor = new dialog_doctor(0);
        if(pDoctor->exec() == QDialog::Accepted)
        {
            adjTable(BaseType::enDoctor);
        }
        delete pDoctor;
    }
    if(TypeBase==BaseType::enLens)
    {
        dialog_lens *pLens = new dialog_lens(0);
        if(pLens->exec() == QDialog::Accepted)
        {
            adjTable(BaseType::enLens);
        }
        delete pLens;
    }
}

void bases::Edit()
{
    qint32 curRow;
    curRow = twTable->currentIndex().row();
    if(curRow<0)
        return;

    if(TypeBase==BaseType::enPatient)
    {
        patient *pPatient = new patient(model->data(model->index(curRow, 1)).toUInt());
        if(pPatient->exec() == QDialog::Accepted)
        {
            adjTable(BaseType::enPatient);
        }
    }

    if(TypeBase==BaseType::enDoctor)
    {
        dialog_doctor *pDoctor = new dialog_doctor(model->data(model->index(curRow, 0)).toUInt());
        if(pDoctor->exec() == QDialog::Accepted)
        {
            adjTable(BaseType::enDoctor);
        }
    }


    if(TypeBase==BaseType::enLens)
    {
        dialog_lens *pLens = new dialog_lens(model->data(model->index(curRow, 0)).toUInt());
        if(pLens->exec() == QDialog::Accepted)
        {
            adjTable(BaseType::enLens);
        }
    }
}

void bases::EditIndex(QModelIndex index)
{
    Edit();
}


void bases::Del()
{
    QString str;
    quint32 curId;
    QSqlQuery query;
    switch (TypeBase)
    {
    case BaseType::enPatient:
        curId = model->data(twTable->model()->index(twTable->currentIndex().row(), 1), Qt::DisplayRole).toUInt();
        str = QString(" DELETE FROM \"patient\" WHERE \"id\"=%1; ")
                .arg(curId);
        query.prepare(str);
        query.exec();
        adjTable(BaseType::enPatient);
        break;
    case BaseType::enDoctor:
        curId = model->data(twTable->model()->index(twTable->currentIndex().row(), 0), Qt::DisplayRole).toUInt();
        str = QString(" DELETE FROM \"doctor\" WHERE \"id\"=%1; ")
                .arg(curId);
        query.prepare(str);
        query.exec();
        adjTable(BaseType::enDoctor);
        break;
    case BaseType::enLens:
        curId = model->data(twTable->model()->index(twTable->currentIndex().row(), 0), Qt::DisplayRole).toUInt();
        str = QString(" DELETE FROM \"lens\" WHERE \"id\"=%1; ")
                .arg(curId);
        query.prepare(str);
        query.exec();
        adjTable(BaseType::enLens);
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

void bases::changeRow(QModelIndex cur, QModelIndex prev)
{
    QString sFio;
    QString sDoc;
    switch(TypeBase)
    {
    case BaseType::enPatient:
        sFio = "Patient: "+model->data(model->index(cur.row(),2)).toString();
        sFio += " ";
        sFio += model->data(model->index(cur.row(),3)).toString();
        sDoc = "Doctor: "+model->data(model->index(cur.row(),4)).toString();
        break;
    default:
        return;
        break;
    }
    emit changeRow(TypeBase, cur.row(), sFio, sDoc);
}
