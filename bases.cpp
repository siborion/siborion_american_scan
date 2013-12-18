#include "bases.h"

bases::bases(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *Layout = new QHBoxLayout(this);

    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();

    QPushButton *pbPatient = new QPushButton(tr("Patient"));
    QPushButton *pbDoctor = new QPushButton(tr("Doctor"));
    QPushButton *pbLens = new QPushButton(tr("Lens Styles"));
    leftLayout->addWidget(pbPatient);
    leftLayout->addWidget(pbDoctor);
    leftLayout->addWidget(pbLens);


    twTable = new QTableWidget(1, 6);
    adjTable();

    rightLayout->addWidget(twTable);



    Layout->addLayout(leftLayout);
    Layout->addLayout(rightLayout);
}


void bases::adjTable()
{
    QStringList lst;
    lst<<tr("Ref.№")<<tr("Patient ID")<<tr("First Name")<<tr("Last Name")<<tr("Doctor Name")<<tr("Notes");
    twTable->setHorizontalHeaderLabels(lst);
    twTable->setColumnWidth(0,50);
    twTable->setColumnWidth(1,50);
    twTable->setColumnWidth(2,50);
}
