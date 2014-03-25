#include "patient.h"

patient::patient(quint32 id, QWidget *parent) :
    QDialog(parent)
{
    QSqlQuery  query;
    QSqlRecord rec;
    QObjectList objectList;

    pBase = scanbase::instanse();

    QGridLayout *layout = new QGridLayout(this);
    QHBoxLayout *buttonLayout  = new QHBoxLayout();

    layout->setSpacing(0);

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
    QLabel  *lLeft       = new QLabel(tr("Left"));
    QLabel  *lRight      = new QLabel(tr("Right"));
    QLabel  *lK1         = new QLabel(tr("K1 - Value"));
    QLabel  *lK2         = new QLabel(tr("K2 - Value"));
    QLabel  *lK          = new QLabel(tr("K  - Value"));

    QLineEdit  *leRef        = new QLineEdit(); leRef->setObjectName("ref");
    QLineEdit  *leId         = new QLineEdit(); leId->setObjectName("id");
    QLineEdit  *leFirstName  = new QLineEdit(); leFirstName->setObjectName("first");
    QLineEdit  *leLastName   = new QLineEdit(); leLastName->setObjectName("last");
    QLineEdit  *leBirth      = new QLineEdit(); leBirth->setObjectName("birth");
    QLineEdit  *leAge        = new QLineEdit(); leAge->setObjectName("age");
    QRadioButton *rbMale     = new QRadioButton(tr("Male"));   rbMale->setObjectName("sex");
    QRadioButton *rbFemale   = new QRadioButton(tr("Female")); rbFemale->setObjectName("female");
    QLineEdit  *leAddress    = new QLineEdit(); leAddress->setObjectName("adress");
    QLineEdit  *leCity       = new QLineEdit(); leCity->setObjectName("city");
    QLineEdit  *leState      = new QLineEdit(); leState->setObjectName("state");
    QLineEdit  *leZip        = new QLineEdit(); leZip->setObjectName("zip");
    QLineEdit  *lePhone      = new QLineEdit(); lePhone->setObjectName("phone");
    QTextEdit  *teNotes      = new QTextEdit();
    QComboBox  *cbDoctor     = new QComboBox();
    QLineEdit  *leK1Left     = new QLineEdit(); leK1Left-> setObjectName("k1left");
    QLineEdit  *leK1Right    = new QLineEdit(); leK1Right->setObjectName("k1right");
    QLineEdit  *leK2Left     = new QLineEdit(); leK2Left-> setObjectName("k2left");
    QLineEdit  *leK2Right    = new QLineEdit(); leK2Right->setObjectName("k2right");
    QLineEdit  *leKLeft     = new QLineEdit();  leKLeft->setObjectName("kleft");
    QLineEdit  *leKRight    = new QLineEdit();  leKRight->setObjectName("kright");
    QSpacerItem *buttonSpacerBot = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

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

    layout->addWidget(lLeft,    14, 1, 1, 1);
    layout->addWidget(lRight,   14, 2, 1, 1);
    layout->addWidget(lK1,      15, 0, 1, 1);
    layout->addWidget(leK1Left, 15, 1, 1, 1);
    layout->addWidget(leK1Right,15, 2, 1, 1);
    layout->addWidget(lK2,      16, 0, 1, 1);
    layout->addWidget(leK2Left, 16, 1, 1, 1);
    layout->addWidget(leK2Right,16, 2, 1, 1);
    layout->addWidget(lK,       17, 0, 1, 1);
    layout->addWidget(leKLeft,  17, 1, 1, 1);
    layout->addWidget(leKRight, 17, 2, 1, 1);
    layout->addItem(buttonSpacerBot, 18, 0, 20, 20);

    buttonLayout->addWidget(pbCancel);
    buttonLayout->addWidget(pbOk);
    layout->addLayout(buttonLayout, 18, 0, 1, 5);
    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));

    query = pBase->getData("select * from patient;");
    if(query.first())
    {
        rec = query.record();
        objectList << this->children();

        for(int i=0; i<objectList.count();i++)
        {
            qint8 recNum = rec.indexOf(objectList.at(i)->objectName());

            if(recNum>=0)
            {
                QLineEdit *c = dynamic_cast<QLineEdit *>(objectList.at(i));
                if(c)
                    c->setText(query.value(recNum).toString());

                QRadioButton *r = dynamic_cast<QRadioButton *>(objectList.at(i));
                if(r)
                    r->setChecked(query.value(recNum).toBool());
            }
        }
    }
}

