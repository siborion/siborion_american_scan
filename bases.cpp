#include "bases.h"

Bases::Bases(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *Layout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QHBoxLayout *topRightLayout  = new QHBoxLayout();
    QHBoxLayout *botRightLayout  = new QHBoxLayout();

    QGroupBox *gbSelect = new QGroupBox();
    QHBoxLayout *groupBoxLayout  = new QHBoxLayout(gbSelect);
    QRadioButton *rbPatient = new QRadioButton(tr(""), gbSelect);
    rbPatient->setObjectName("rbPatient");
    rbPatient->setChecked(true);
    QRadioButton *rbDoctor  = new QRadioButton(tr(""), gbSelect);
    rbDoctor->setObjectName("rbDoctor");
    QRadioButton *rbLens    = new QRadioButton(tr("Lens Styles"), gbSelect);
    rbLens->setObjectName("rbLens");
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

    lSearch  = new QLabel(tr("Search"));
    leSearch = new QLineEdit();

    model = new QSqlQueryModel ();
    pTest = new QPushButton();
    pbAdd = new QPushButton();
    pbEdit = new QPushButton();
    pbDel = new QPushButton();
    pbPatientHistory = new QPushButton();

    twTable = new adjview();
    twTable->setModel(model);
    twTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    twTable->setSelectionMode(QAbstractItemView::SingleSelection);

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

    numRowPatient = -1;
    typeBase = Base::enPatient;

    connect(rbPatient, SIGNAL(clicked(bool)), SLOT(changeBase(bool)));
    connect(rbDoctor, SIGNAL(clicked(bool)), SLOT(changeBase(bool)));
    connect(rbLens, SIGNAL(clicked(bool)), SLOT(changeBase(bool)));
    connect(pbAdd,  SIGNAL(pressed()), SLOT(Add()));
    connect(pbEdit, SIGNAL(pressed()), SLOT(Edit()));
    connect(pbDel, SIGNAL(pressed()), SLOT(Del()));
    connect(twTable, SIGNAL(doubleClicked(QModelIndex)), SLOT(EditIndex(QModelIndex)));
}

void Bases::adjTable()
{
    emit getModel(typeBase, &model);

    QStringList lstButton;
    QList<int>  columnPercent;
    twTable->setModel(model);

    switch (typeBase)
    {
    case Base::enPatient:
        columnPercent<<   8        <<    30     <<       30        <<     30;
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient")<<tr("Patient History");
        if(model->rowCount()<=numRowPatient)
            numRowPatient = model->rowCount()-1;
        twTable->selectRow(numRowPatient);
        break;
    case Base::enDoctor:
        columnPercent   <<       8        <<      30        <<      30       <<     30;
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        break;
    case Base::enLens:
        columnPercent   << 0 <<            8       <<      20      <<      20         <<     20    <<      20    <<      10;
        lstButton<<tr("Add Lens")<<tr("Edit Lens")<<tr("Delete Lens");
        break;
    }
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

void Bases::setStPatient(QMap <QString, QString> *stPatientBases)
{
    stPatient = stPatientBases;
}

void Bases::changeBase(bool Val)
{
    if(Val)
    {
        QObject* sender = const_cast<QObject*>(QObject::sender());
        if(sender->objectName() == "rbPatient")
            typeBase = Base::enPatient;
        if(sender->objectName() == "rbDoctor")
            typeBase = Base::enDoctor;
        if(sender->objectName() == "rbLens")
            typeBase = Base::enLens;
        adjTable();
    }
}

void Bases::Add()
{
    quint16 newId;
    if(typeBase==Base::enPatient)
    {
        emit updateCurPatient(0);
        Dialog_Patient *pPatient = new Dialog_Patient(stPatient);
        if(pPatient->exec() == QDialog::Accepted)
            emit savePatient(&newId);
        adjTable();
        delete pPatient;
    }
    if(typeBase==Base::enDoctor)
    {
        Dialog_Doctor *pDoctor = new Dialog_Doctor(0);
        if(pDoctor->exec() == QDialog::Accepted)
        {
            adjTable();
        }
        delete pDoctor;
    }
    if(typeBase==Base::enLens)
    {
        Dialog_Lens *pLens = new Dialog_Lens(0);
        if(pLens->exec() == QDialog::Accepted)
        {
            adjTable();
        }
        delete pLens;
    }
}

void Bases::Edit()
{
    quint16 newId;
    if(typeBase==Base::enPatient)
    {
        Dialog_Patient *pPatient = new Dialog_Patient(stPatient);
        if(pPatient->exec() == QDialog::Accepted)
        {
            emit savePatient(&newId);
            adjTable();
        }
    }
}

void Bases::EditIndex(QModelIndex index)
{
    Q_UNUSED(index);
    Edit();
}

void Bases::Del()
{
    if(typeBase==Base::enPatient)
        emit delPatient();
    adjTable();
}

void Bases::changeRow(QModelIndex cur, QModelIndex prev)
{
    quint16 rowId;
    Q_UNUSED(cur); Q_UNUSED(prev);
    if(typeBase == Base::enPatient)
    {
       numRowPatient = twTable->currentIndex().row();
       rowId = (quint16)model->data(twTable->model()->index(twTable->currentIndex().row(),0),Qt::DisplayRole).toUInt();
       emit updateCurPatient(rowId);
    }
}

void Bases::Init()
{
    typeBase = Base::enPatient;
    adjTable();
    connect(twTable->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex,QModelIndex)));
    emit updateCurPatient(0);
}
