#include "patient.h"

patient::patient(quint32 id, QWidget *parent) :
    QDialog(parent)
{
    patientId = id;

    pBase = scanbase::instanse();

    model = new QSqlTableModel ();
    model->setTable("doctor");
    if(model->select())
    {
        qDebug()<<"555555";
    }

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

    QLineEdit  *leRef        = new QLineEdit(); leRef->setObjectName("VALref");
    QLineEdit  *leId         = new QLineEdit(); leId->setObjectName("id");
    QLineEdit  *leFirstName  = new QLineEdit(); leFirstName->setObjectName("VALfirst");
    QLineEdit  *leLastName   = new QLineEdit(); leLastName->setObjectName("VALlast");
    QLineEdit  *leBirth      = new QLineEdit(); leBirth->setObjectName("VALbirth");
    QLineEdit  *leAge        = new QLineEdit(); leAge->setObjectName("VALage");
    QRadioButton *rbMale     = new QRadioButton(tr("Male"));   rbMale->setObjectName("VALsex0");
    QRadioButton *rbFemale   = new QRadioButton(tr("Female")); rbFemale->setObjectName("VALsex1");
    QLineEdit  *leAddress    = new QLineEdit(); leAddress->setObjectName(" VALadress");
    QLineEdit  *leCity       = new QLineEdit(); leCity->setObjectName("VALcity");
    QLineEdit  *leState      = new QLineEdit(); leState->setObjectName("VALstate");
    QLineEdit  *leZip        = new QLineEdit(); leZip->setObjectName("VALzip");
    QLineEdit  *lePhone      = new QLineEdit(); lePhone->setObjectName("VALphone");
    QTextEdit  *teNotes      = new QTextEdit(); teNotes->setObjectName("VALnotes");
    QComboBox  *cbDoctor     = new QComboBox(); cbDoctor->setObjectName("VALdoctor");
    QLineEdit  *leK1Left     = new QLineEdit(); leK1Left-> setObjectName("VALk1left");
    QLineEdit  *leK1Right    = new QLineEdit(); leK1Right->setObjectName("VALk1right");
    QLineEdit  *leK2Left     = new QLineEdit(); leK2Left-> setObjectName("VALk2left");
    QLineEdit  *leK2Right    = new QLineEdit(); leK2Right->setObjectName("VALk2right");
    QLineEdit  *leKLeft     = new QLineEdit();  leKLeft->setObjectName("VALkleft");
    QLineEdit  *leKRight    = new QLineEdit();  leKRight->setObjectName("VALkright");
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
    connect(pbOk, SIGNAL(clicked()), SLOT(save()));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));

    cbDoctor->setModel(model);
    cbDoctor->setModelColumn(model->fieldIndex("name"));
    findRecord(model, 0);

    fillData();
}

void patient::fillData()
{
    QString str;
    QSqlQuery  query;
    QSqlRecord rec;
    QObjectList objectList;

    str = "select * from patient where id = %1 ;";
    str = str.arg(patientId);
    query = pBase->getData(str);
    if(query.first())
    {
        QString sObName;
        quint8 val;
        rec = query.record();
        objectList << this->children();

        for(int i=0; i<objectList.count();i++)
        {
            sObName = objectList.at(i)->objectName();
            if(sObName.left(3) == "VAL")
            {
                sObName = sObName.right(sObName.count()-3);
                QLineEdit *c = dynamic_cast<QLineEdit *>(objectList.at(i));
                if(c)
                {
                    qint8 recNum = rec.indexOf(sObName);
                    if(recNum>=0)
                        c->setText(query.value(recNum).toString());
                }

                QRadioButton *r = dynamic_cast<QRadioButton *>(objectList.at(i));
                if(r)
                {
                    str = sObName.left(sObName.count()-1);
                    qint8 recNum = rec.indexOf(str);
                    if(recNum>=0)
                    {
                        val = query.value(recNum).toUInt();
                        str.append(QString("%1").arg(val));
                        if(sObName == str)
                            r->setChecked(true);
                    }
                }

                QTextEdit *t = dynamic_cast<QTextEdit *>(objectList.at(i));
                if(t)
                {
                    qint8 recNum = rec.indexOf(sObName);
                    if(recNum>=0)
                        t->setText(query.value(recNum).toString());
                }

                QComboBox *b = dynamic_cast<QComboBox *>(objectList.at(i));
                if(b)
                {
                    qint8 recNum = rec.indexOf(sObName);
                    if(recNum>=0)
                    {
                        val = query.value(recNum).toUInt();
                        if(sObName == "doctor")
                            b->setCurrentIndex(findRecord(model, val));
                    }
                }
            }
        }
    }
}

int patient::findRecord(QSqlTableModel *tableModel, quint32 id)
{
    for(int i=0; i<tableModel->rowCount(); i++)
    {
        if(id == tableModel->index(i, 0).data(Qt::DisplayRole).toUInt())
            return i;
    }
    return (-1);
}

void patient::save()
{
    QString strUpdate;
    QString strUpdateValue;
    QSqlQuery  query;
    QSqlRecord rec;
    QObjectList objectList;
    QString sObName;
    QString strInsertColumn;
    QString strInsertValue;

    strUpdate = "update patient set id=id";
    strInsertColumn = "insert into patient (";
    strInsertValue = " values (";

    objectList << this->children();

    for(int i=0; i<objectList.count();i++)
    {
        sObName = objectList.at(i)->objectName();

        if(sObName.left(3) == "VAL")
        {
            sObName = sObName.right(sObName.count()-3);
            strUpdateValue = "";

            QLineEdit *c = dynamic_cast<QLineEdit *>(objectList.at(i));
            if(c)
                strUpdateValue = c->text();

            QTextEdit *t = dynamic_cast<QTextEdit *>(objectList.at(i));
            if(t)
                strUpdateValue = t->toPlainText();

            QComboBox *b = dynamic_cast<QComboBox *>(objectList.at(i));
            if(b)
                strUpdateValue = QString("%1").arg(b->model()->data(b->model()->index(b->currentIndex(), 0)).toUInt());

            QRadioButton *r = dynamic_cast<QRadioButton *>(objectList.at(i));
            if(r)
            {
                QString rbStr="";
                rbStr = sObName.right(1);
                sObName = sObName.left(sObName.count()-1);
                if(r->isChecked())
                    strUpdateValue = rbStr;
            }

            if(!strUpdateValue.isEmpty())
            {
                strUpdate.append(QString(",\"%1\"='%2'").arg(sObName).arg(strUpdateValue));
                strInsertColumn.append(QString("\"%1\",").arg(sObName));
                strInsertValue.append(QString("'%1',").arg(strUpdateValue));
            }
        }
    }
    strInsertColumn=strInsertColumn.mid(0,strInsertColumn.count()-1);
    strInsertColumn.append(") ");
    strInsertValue =strInsertValue.mid (0,strInsertValue.count()-1);
    strInsertValue.append(") ");
    strInsertColumn.append(strInsertValue);
    strUpdate.append(QString(" where id=%1;").arg(patientId));

    if(patientId>0)
        query.prepare(strUpdate);
    else
        query.prepare(strInsertColumn);
    qDebug() << query.exec();
    qDebug() << strUpdate;
    qDebug() << strInsertColumn;
    accept();
}
