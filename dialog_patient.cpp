#include "dialog_patient.h"

Dialog_Patient::Dialog_Patient(QMap <QString, QString> *stPatient, QWidget *parent) :
    QDialog(parent)
{
    model = new QSqlTableModel ();
    model->setTable("v_cbdoctor");
    model->select();

    QGridLayout *layout = new QGridLayout(this);
    QHBoxLayout *buttonLayout  = new QHBoxLayout();

    layout->setSpacing(0);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    QPushButton *pbOk = new QPushButton(tr("Save"));

    QLabel  *lId         = new QLabel(tr("Patient ID"));
    QLabel  *lFirstName  = new QLabel(tr("First Name"));
    QLabel  *lLastName   = new QLabel(tr("Last Name"));
    QLabel  *lBirth      = new QLabel(tr("Date Of Birth"));
    QLabel  *lAge        = new QLabel(tr("Age Today"));
    QLabel  *lSex        = new QLabel(tr("Sex"));
    QLabel  *lAddress    = new QLabel(tr("Adress"));
    QLabel  *lCity       = new QLabel(tr("City"));
    QLabel  *lState      = new QLabel(tr("State"));
    QLabel  *lZip        = new QLabel(tr("Zip"));
    QLabel  *lPhone      = new QLabel(tr("Phone"));
    QLabel  *lNotes      = new QLabel(tr("Notes"));
    QLabel  *lDoctor     = new QLabel(tr("Doctor"));
    QLabel  *lLeft       = new QLabel(tr("Left"));
    QLabel  *lRight      = new QLabel(tr("Right"));
    QLabel  *lK1         = new QLabel(tr("K1 - Value"));
    QLabel  *lK2         = new QLabel(tr("K2 - Value"));
    QLabel  *lK          = new QLabel(tr("K  - Value"));

    QLineEdit  *leId         = new QLineEdit(); leId->setObjectName("VALid");    leId->setEnabled(false);
    QLineEdit  *leFirstName  = new QLineEdit(); leFirstName->setObjectName("VALname");
    QLineEdit  *leLastName   = new QLineEdit(); leLastName->setObjectName("VALlast");
    QDateEdit  *leBirth      = new QDateEdit(); leBirth->setObjectName("VALbirth");
    leBirth->setDisplayFormat("MM.dd.yyyy");
    leAge        = new QLineEdit(); leAge->setObjectName("VALage");
    QRadioButton *rbMale     = new QRadioButton(tr("Male"));   rbMale->setObjectName("VALsex0");
    QRadioButton *rbFemale   = new QRadioButton(tr("Female")); rbFemale->setObjectName("VALsex1");
    QLineEdit  *leAddress    = new QLineEdit(); leAddress->setObjectName("VALadress");
    QLineEdit  *leCity       = new QLineEdit(); leCity->setObjectName("VALcity");
    QLineEdit  *leState      = new QLineEdit(); leState->setObjectName("VALstate");
    QLineEdit  *leZip        = new QLineEdit(); leZip->setObjectName("VALzip");
    QLineEdit  *lePhone      = new QLineEdit(); lePhone->setObjectName("VALphone");
    QTextEdit  *teNotes      = new QTextEdit(); teNotes->setObjectName("VALnotes");
    QComboBox  *cbDoctor     = new QComboBox(); cbDoctor->setObjectName("VALdoctor");
    leK1Left     = new QLineEdit(); leK1Left-> setObjectName("VALk1left");
    leK1Right    = new QLineEdit(); leK1Right->setObjectName("VALk1right");
    leK2Left     = new QLineEdit(); leK2Left-> setObjectName("VALk2left");
    leK2Right    = new QLineEdit(); leK2Right->setObjectName("VALk2right");
    leKLeft     = new QLineEdit();  leKLeft->setObjectName("VALkleft");
    leKRight    = new QLineEdit();  leKRight->setObjectName("VALkright");
    QSpacerItem *buttonSpacerBot = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(lId,       1, 0);
    layout->addWidget(lFirstName,2, 0);
    layout->addWidget(lLastName, 3, 0);
    layout->addWidget(lBirth,    4, 0);
    layout->addWidget(lAge,      5, 0);
    layout->addWidget(lSex,      6, 0);
    layout->addWidget(lAddress,  7, 0);
    layout->addWidget(lCity,     8, 0);
    layout->addWidget(lState,    9, 0);
    layout->addWidget(lZip,      10, 0);
    layout->addWidget(lPhone,    11, 0);
    layout->addWidget(lNotes,    12, 0);
    layout->addWidget(lDoctor,   13, 0);

    layout->addWidget(leId,       1, 1, 1, 1);
    layout->addWidget(leFirstName,2, 1, 1, 2);
    layout->addWidget(leLastName, 3, 1, 1, 2);
    layout->addWidget(leBirth,    4, 1, 1, 2);
    layout->addWidget(leAge,      5, 1, 1, 2);
    layout->addWidget(rbMale,     6, 1, 1, 1); layout->addWidget(rbFemale,     6, 2, 1, 1);
    layout->addWidget(leAddress,  7, 1, 1, 2);
    layout->addWidget(leCity,     8, 1, 1, 2);
    layout->addWidget(leState,    9, 1, 1, 2);
    layout->addWidget(leZip,      10, 1, 1, 2);
    layout->addWidget(lePhone,    11, 1, 1, 2);
    layout->addWidget(teNotes,    12, 1, 1, 2);
    layout->addWidget(cbDoctor,   13, 1, 1, 2);

    layout->addWidget(lLeft,    14, 1, 1, 1);
    layout->addWidget(lRight,   14, 2, 1, 1);

    layout->addWidget(lK1,      15, 0, 1, 1);
    layout->addWidget(leK1Left, 15, 1, 1, 1);

    layout->addWidget(lK2,      16, 0, 1, 1);
    layout->addWidget(leK2Left, 16, 1, 1, 1);

    layout->addWidget(leKLeft,  17, 1, 1, 1);
    layout->addWidget(lK,       17, 0, 1, 1);

    layout->addWidget(leK1Right,15, 2, 1, 1);
    layout->addWidget(leK2Right,16, 2, 1, 1);
    layout->addWidget(leKRight, 17, 2, 1, 1);

    layout->addItem(buttonSpacerBot, 18, 0, 20, 20);

    leKLeft->setEnabled(false);
    leKRight->setEnabled(false);
    leAge->setEnabled(false);


    buttonLayout->addWidget(pbCancel);
    buttonLayout->addWidget(pbOk);
    layout->addLayout(buttonLayout, 18, 0, 1, 5);

    connect(pbOk, SIGNAL(clicked()), SLOT(saveData()));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    connect(leK1Left, SIGNAL(textChanged(QString)),  SLOT(kLeftAverage()));
    connect(leK2Left, SIGNAL(textChanged(QString)),  SLOT(kLeftAverage()));
    connect(leK1Right, SIGNAL(textChanged(QString)), SLOT(kRightAverage()));
    connect(leK2Right, SIGNAL(textChanged(QString)), SLOT(kRightAverage()));
    connect(leK2Right, SIGNAL(textChanged(QString)), SLOT(kRightAverage()));
    connect(leBirth, SIGNAL(dateChanged(QDate)),   SLOT(calculateAge(QDate)));

    cbDoctor->setModel(model);
    cbDoctor->setModelColumn(model->fieldIndex("name"));

    pBaseFill = new basefill(children(), stPatient);
    pBaseFill->fillData();
}

void Dialog_Patient::saveData()
{
    pBaseFill->saveData();
    accept();
}

void Dialog_Patient::kLeftAverage()
{
    double dTmp;
    dTmp  = leK1Left->text().toDouble()+leK2Left->text().toDouble();
    dTmp /= 2;
    leKLeft->setText(QString("%1").arg(dTmp));
}

void Dialog_Patient::kRightAverage()
{
    double dTmp;
    dTmp  = leK1Right->text().toDouble()+leK2Right->text().toDouble();
    dTmp /= 2;
    leKRight->setText(QString("%1").arg(dTmp));
}

void Dialog_Patient::calculateAge(QDate val)
{
    quint8 age;
    age = (QDate::currentDate().year() - val.year());
    leAge->setText(QString("%1").arg(age));
}
