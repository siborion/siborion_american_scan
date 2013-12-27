#include "patient.h"

patient::patient(QWidget *parent) :
    QDialog(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    QHBoxLayout *buttonLayout  = new QHBoxLayout();

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    QPushButton *pbOk = new QPushButton(tr("Ok"));

    QLabel  *lRef        = new QLabel(tr("Ref. No"));
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

    QLineEdit  *leRef        = new QLineEdit();
    QLineEdit  *leId         = new QLineEdit();
    QLineEdit  *leFirstName  = new QLineEdit();
    QLineEdit  *leLastName   = new QLineEdit();
    QLineEdit  *leBirth      = new QLineEdit();
    QLineEdit  *leAge        = new QLineEdit();
    QRadioButton *rbMale     = new QRadioButton(tr("Male"));
    QRadioButton *rbFemale   = new QRadioButton(tr("Female"));
    QLineEdit  *leAddress    = new QLineEdit();
    QLineEdit  *leCity       = new QLineEdit();
    QLineEdit  *leState      = new QLineEdit();
    QLineEdit  *leZip        = new QLineEdit();
    QLineEdit  *lePhone      = new QLineEdit();
    QTextEdit  *teNotes      = new QTextEdit();
    QComboBox  *cbDoctor     = new QComboBox();

    layout->addWidget(lRef,      0, 0);
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

    layout->addWidget(leRef,      0, 1, 1, 1);
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

    buttonLayout->addWidget(pbCancel);
    buttonLayout->addWidget(pbOk);
    layout->addLayout(buttonLayout, 15, 0, 1, 5);
    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
}
