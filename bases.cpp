#include "bases.h"

bases::bases(QWidget *parent) :
    QWidget(parent)
{
//    QPalette Pal(palette());
//    Pal.setColor(QPalette::Background, Qt::gray);
//    setAutoFillBackground(true);
//    setPalette(Pal);

//    QByteArray line;
//    QFile file("in.svg");
//       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//           return;
//
//       while (!file.atEnd()) {
//           line.append(file.readLine());
//       }

    QHBoxLayout *Layout = new QHBoxLayout(this);

    QVBoxLayout *leftLayout  = new QVBoxLayout();
    QGridLayout *rightLayout = new QGridLayout();
    QHBoxLayout *topRightLayout  = new QHBoxLayout();
    QHBoxLayout *botRightLayout  = new QHBoxLayout();

//    QSpacerItem *buttonSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//    QPushButton *pbPatient = new QPushButton(tr("Patient"));
//    QPushButton *pbDoctor = new QPushButton(tr("Doctor"));
//    QPushButton *pbLens = new QPushButton(tr("Lens Styles"));
//    pbPatient->setMinimumHeight(50);
//    pbDoctor->setMinimumHeight(50);
//    pbLens->setMinimumHeight(50);
//    QSpacerItem *buttonSpacerBot = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

//    leftLayout->addItem(buttonSpacerTop);
//    leftLayout->addWidget(pbPatient);
//    leftLayout->addWidget(pbDoctor);
//    leftLayout->addWidget(pbLens);

//    QGroupBox *gbSelect = new QGroupBox();
//    QVBoxLayout *groupBoxLayout  = new QVBoxLayout(gbSelect);
//    QRadioButton *rbPatient = new QRadioButton(tr("Patient"), gbSelect);
//    QRadioButton *rbDoctor  = new QRadioButton(tr("Doctor"), gbSelect);
//    QRadioButton *rbLens    = new QRadioButton(tr("Lens Styles"), gbSelect);
//    groupBoxLayout->addWidget(rbPatient);
//    groupBoxLayout->addWidget(rbDoctor);
//    groupBoxLayout->addWidget(rbLens);
//    leftLayout->addWidget(gbSelect);

//    leftLayout->addItem(buttonSpacerBot);


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

    model = new QStandardItemModel();
    pTest = new QPushButton();
    pbAdd = new QPushButton();
    pbEdit = new QPushButton();
    pbDel = new QPushButton();
    pbPatientHistory = new QPushButton();

    twTable = new adjview();
    twTable->setModel(model);

    topRightLayout->addWidget(gbSelect);
    topRightLayout->addWidget(lSearch);
    topRightLayout->addWidget(leSearch);

//    QString t = "in.txt";
//    svg = new QString();
//    tmp = new QSvgWidget();
//    tmp->load(QString( "in.svg" ));
//    tmp->setMinimumSize(50,50);
//    tmp->setMaximumSize(50,50);
//    QSvgRenderer qSvg;
//    qSvg.load(line);
//    QPixmap pix(90, 90);
//    QPainter painter;
//    painter.begin(&pix);
//    painter.fillRect(QRect(0,0,90,90), QColor(0,255,0,100));
//    qSvg.render(&painter);
//    painter.end();
//    QIcon icon;
//    icon.addPixmap(pix);
//    pTest->setMinimumHeight(100);
//    pTest->setIcon(icon);
//    pTest->setIconSize(QSize(100,100));
//    botRightLayout->addWidget(tmp);
//    botRightLayout->addWidget(pTest);

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

//    connect(pbPatient, SIGNAL(pressed()), SLOT(changeBasePatient()));
//    connect(pbDoctor, SIGNAL(pressed()), SLOT(changeBaseDoctor()));
//    connect(pbLens, SIGNAL(pressed()), SLOT(changeBaseLens()));
    connect(rbPatient, SIGNAL(clicked(bool)), SLOT(changeBasePatient(bool)));
    connect(rbDoctor, SIGNAL(clicked(bool)), SLOT(changeBaseDoctor(bool)));
    connect(rbLens, SIGNAL(clicked(bool)), SLOT(changeBaseLens(bool)));

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
        columnPercent<<10   <<   10        <<      20        <<      20       <<       20        <<     20;
        lst<<tr("Ref.№")<<tr("Patient ID")<<tr("First Name")<<tr("Last Name")<<tr("Doctor Name")<<tr("Notes");
        lstButton<<tr("Add Patient")<<tr("Edit Patient")<<tr("Delete Patient")<<tr("Patient History");
        break;
    case enDoctor:
        columnPercent   <<       10        <<      30        <<      30       <<     30;
        lst             <<tr("Doctor Id") <<tr("First Name")<<tr("Last Name")<<tr("Notes");
        lstButton<<tr("Add Doctor")<<tr("Edit Doctor")<<tr("Delete Doctor");
        break;
    case enLens:
        columnPercent   <<       10       <<      20      <<      20         <<     20    <<      20    <<      10;
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

void bases::changeBasePatient(bool Val)
{
    if(Val)
        adjTable(enPatient);
}
void bases::changeBaseDoctor(bool Val)
{
    if(Val)
        adjTable(enDoctor);
}
void bases::changeBaseLens(bool Val)
{
    if(Val)
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
//            qDebug() << pDoctor->modelDoctor->item(0,1)->text();
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
