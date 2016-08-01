#include "bases.h"

Bases::Bases(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *Layout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QVBoxLayout *topRightLayout  = new QVBoxLayout();
    //    QHBoxLayout *botRightLayout  = new QHBoxLayout();

    QGroupBox *gbSelect = new QGroupBox();
    QVBoxLayout *groupBoxLayout  = new QVBoxLayout(gbSelect);
    QRadioButton *rbPatient = new QRadioButton(tr(""), gbSelect);
    rbPatient->setObjectName("rbPatient");
    rbPatient->setChecked(true);
    QRadioButton *rbDoctor  = new QRadioButton(tr(""), gbSelect);
    rbDoctor->setObjectName("rbDoctor");
    QRadioButton *rbLens    = new QRadioButton(tr("IOLs"), gbSelect);
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

    QGroupBox   *gbPushButton = new QGroupBox();
    gbPushButton->setMaximumWidth(200);
    QVBoxLayout *hlPushButton1 = new QVBoxLayout();
    QHBoxLayout *hlPushButton2 = new QHBoxLayout();
    QVBoxLayout *vlPushButton = new QVBoxLayout();
    gbPushButton->setLayout(vlPushButton);
    hlPushButton2->addWidget(lSearch);
    hlPushButton2->addWidget(leSearch);
    hlPushButton1->addWidget(pbAdd);
    hlPushButton1->addWidget(pbEdit);
    hlPushButton1->addWidget(pbDel);
    vlPushButton->addLayout(hlPushButton1);
    vlPushButton->addLayout(hlPushButton2);


    //    QSpacerItem *horizontalSpacer = new QSpacerItem (40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);


    topRightLayout->addWidget(gbSelect);
    topRightLayout->addWidget(gbPushButton);
    //    topRightLayout->addItem(horizontalSpacer);

    //    topRightLayout->addWidget(lSearch);
    //    topRightLayout->addWidget(leSearch);

    //    topRightLayout->addWidget(pbAdd);
    //    topRightLayout->addWidget(pbEdit);
    //    topRightLayout->addWidget(pbDel);
    //    topRightLayout->addWidget(pbPatientHistory);

    //    botRightLayout->addWidget(pbAdd);
    //    botRightLayout->addWidget(pbEdit);
    //    botRightLayout->addWidget(pbDel);
    //    botRightLayout->addWidget(pbPatientHistory);

    rightLayout->addLayout(topRightLayout, 0, 0);
    rightLayout->addWidget(twTable,        0, 1);
    //    rightLayout->addLayout(botRightLayout, 0, 0);

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
        columnPercent<<   8        <<    30     <<       30  << 30;
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient");
        if(model->rowCount()<=numRowPatient)
            numRowPatient = model->rowCount()-1;
        twTable->selectRow(numRowPatient);
        break;
    case Base::enDoctor:
        columnPercent   <<       8        <<      30        <<      30       <<     30;
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        break;
    case Base::enLens:
        columnPercent   << 0 <<            8       <<      20      <<      15         <<     15    <<      15    <<      10 << 5<<5<<5;
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

void Bases::setStDoctor(QMap <QString, QString> *stDoctorBases)
{
    stDoctor = stDoctorBases;
}

void Bases::setStLens(QMap <QString, QString> *stLensBases)
{
    stLens = stLensBases;
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
        qDebug()<<"changeBase";
        connect(twTable->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex,QModelIndex)));
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
        {
            emit savePatient(&newId);
            emit updateCurPatient(newId);
            adjTable();
            twTable->selectRow(twTable->model()->rowCount()-1);
        }
        delete pPatient;
    }
    if(typeBase==Base::enDoctor)
    {
        emit updateCurDoctor(0);
        Dialog_Doctor *pDoctor = new Dialog_Doctor(stDoctor);
        if(pDoctor->exec() == QDialog::Accepted)
        {
            emit saveDoctor(&newId);
            emit saveDocLens(newId, &pDoctor->idLens);
        }
        adjTable();
        delete pDoctor;
    }
    if(typeBase==Base::enLens)
    {
        emit updateCurLens(0);
        Dialog_Lens *pLens = new Dialog_Lens(stLens);
        if(pLens->exec() == QDialog::Accepted)
        {
            emit saveLens(&newId);
        }
        adjTable();
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
    if(typeBase==Base::enDoctor)
    {
        Dialog_Doctor *pDoctor = new Dialog_Doctor(stDoctor);
        if(pDoctor->exec() == QDialog::Accepted)
        {
            emit saveDoctor(&newId);
            emit saveDocLens(newId, &pDoctor->idLens);
            adjTable();
        }
    }
    if(typeBase==Base::enLens)
    {
        Dialog_Lens *pLens = new Dialog_Lens(stLens);
        if(pLens->exec() == QDialog::Accepted)
        {
            emit saveLens(&newId);
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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Do you want delete?");
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec()==QMessageBox::Yes)
    {

        if(typeBase==Base::enPatient)
            emit delPatient();
        if(typeBase==Base::enDoctor)
            emit delDoctor();
        if(typeBase==Base::enLens)
            emit delLens();
        adjTable();
    }
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
        twTable->setFocus();
    }
    if(typeBase == Base::enDoctor)
    {
        rowId = (quint16)model->data(twTable->model()->index(twTable->currentIndex().row(),0),Qt::DisplayRole).toUInt();
        emit updateCurDoctor(rowId);
    }
    if(typeBase == Base::enLens)
    {
        rowId = (quint16)model->data(twTable->model()->index(twTable->currentIndex().row(),0),Qt::DisplayRole).toUInt();
        emit updateCurLens(rowId);
    }
}

void Bases::Init()
{
    typeBase = Base::enPatient;
    adjTable();
    connect(twTable->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(changeRow(QModelIndex,QModelIndex)));
    emit updateCurPatient(0);
}
