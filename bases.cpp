#include "bases.h"

bases::bases(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *Layout = new QHBoxLayout(this);

    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QHBoxLayout *topRightLayout  = new QHBoxLayout();
    QHBoxLayout *botRightLayout  = new QHBoxLayout();

    QPushButton *pbPatient = new QPushButton(tr("Patient"));
    QPushButton *pbDoctor = new QPushButton(tr("Doctor"));
    QPushButton *pbLens = new QPushButton(tr("Lens Styles"));
    leftLayout->addWidget(pbPatient);
    leftLayout->addWidget(pbDoctor);
    leftLayout->addWidget(pbLens);


    QLabel    *lSearch  = new QLabel(tr("Search"));
    QLineEdit *leSearch = new QLineEdit();
    twTable = new QTableWidget(0, 6);
    pbAdd = new QPushButton();
    pbEdit = new QPushButton();
    pbDel = new QPushButton();
    QPushButton *pbPatientHistory = new QPushButton(tr("Patient History"));


    topRightLayout->addWidget(lSearch);
    topRightLayout->addWidget(leSearch);

    botRightLayout->addWidget(pbAdd);
    botRightLayout->addWidget(pbEdit);
    botRightLayout->addWidget(pbDel);
    botRightLayout->addWidget(pbPatientHistory);

    rightLayout->addLayout(topRightLayout, 0, 0);
    rightLayout->addWidget(twTable,          1, 0, 1, 1);
    rightLayout->addLayout(botRightLayout, 2, 0);

    adjTable();

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
    pbAdd->setText(tr("Add Patient"));
    pbEdit->setText(tr("Edit Patient"));
    pbDel->setText(tr("Delete Patient"));

}
