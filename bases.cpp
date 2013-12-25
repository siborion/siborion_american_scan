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

    twTable = new QTableView();
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
}

void bases::adjTable(quint8 Val)
{
    QStringList lst;
    QStringList lstButton;
    TypeBase = Val;
    switch (TypeBase)
    {
    case enPatient:
        lst<<tr("Ref.№")<<tr("Patient ID")<<tr("First Name")<<tr("Last Name")<<tr("Doctor Name")<<tr("Notes");
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient")<<tr("Patient History");
        break;
    case enDoctor:
        lst<<tr("Doctor Id")<<tr("First Name")<<tr("Last Name")<<tr("Notes");
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        break;
    case enLens:
        lst<<tr("Lens Name")<<tr("Mfg Name")<<tr("Mfg A_Const")<<tr("Mfg ACD")<<tr("Mfg SF")<<tr("Hoffer ACD");
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

    adjCol();
}

void bases::resizeEvent( QResizeEvent *__e )
{
    QResizeEvent *tmp;  //заглушка
    tmp = __e;          //
    tmp->oldSize();     //
    adjCol();
}

void bases::adjCol()
{
    quint16 uiWidth;
    quint8 ColCount;
    ColCount = model->columnCount();
    uiWidth = (twTable->width()-ColCount)/ColCount;
    for(quint8 i=0; i<ColCount; i++)
    {
        twTable->setColumnWidth(i, uiWidth);
    }
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
