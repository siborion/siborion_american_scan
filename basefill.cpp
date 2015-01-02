#include "basefill.h"

basefill::basefill(const QObjectList &list, QMap<QString,QString> *table)
{
    olParent = &list;
    qmTable = table;
}

void basefill::fillData()
{
    QString str;
    QString sObName;

    for(int i=0; i<olParent->count();i++)
    {
        sObName = olParent->at(i)->objectName();
        if(sObName.left(3) == "VAL")
        {
            sObName = sObName.right(sObName.count()-3);

            QDateEdit *d = dynamic_cast<QDateEdit *>(olParent->at(i));
            if(d)
            {
                QString sTmp;
                if(qmTable->contains(sObName))
                {
                    sTmp = qmTable->value(sObName,"");
                    QDate dTmp = QDate::fromString(sTmp, "MM.dd.yyyy");
                    d->setDate(dTmp);
                }
            }

            QLineEdit *c = dynamic_cast<QLineEdit *>(olParent->at(i));
            if(c)
            {
                if(qmTable->contains(sObName))
                    c->setText(qmTable->value(sObName,""));
            }

            QRadioButton *r = dynamic_cast<QRadioButton *>(olParent->at(i));
            if(r)
            {
                str = sObName.left(sObName.count()-1);
                if(qmTable->contains(str))
                {
                    qint8 radioNum = qmTable->value(str,0).toInt();
                    str.append(QString("%1").arg(radioNum));
                    if(sObName == str)
                        r->setChecked(true);
                }
            }

            QTextEdit *t = dynamic_cast<QTextEdit *>(olParent->at(i));
            if(t)
            {
                if(qmTable->contains(sObName))
                    t->setText(qmTable->value(sObName,""));
            }

            QComboBox *b = dynamic_cast<QComboBox *>(olParent->at(i));
            if(b)
            {
                if(qmTable->contains(sObName))
                {
                    quint16 recNum = qmTable->value(sObName,"").toUInt();
                    for(int i=0; i<b->model()->rowCount(); i++)
                    {
                        QModelIndex parentIndex = b->model()->index(i, 0);
                        if(parentIndex.data().toInt() == recNum)
                            b->setCurrentIndex(i);
                    }
                }
            }
        }
    }
}

void basefill::saveData()
{
    QString sObName;
    for(int i=0; i<olParent->count();i++)
    {
        sObName = olParent->at(i)->objectName();
        if(sObName.left(3) == "VAL")
        {
            sObName = sObName.right(sObName.count()-3);

            QDateEdit *d = dynamic_cast<QDateEdit *>(olParent->at(i));
            if((d)&&qmTable->contains(sObName))
                qmTable->insert(sObName, d->text());

            QLineEdit *c = dynamic_cast<QLineEdit *>(olParent->at(i));
            if((c)&&qmTable->contains(sObName))
                qmTable->insert(sObName, c->text());

            QTextEdit *t = dynamic_cast<QTextEdit *>(olParent->at(i));
            if((t)&&qmTable->contains(sObName))
                qmTable->insert(sObName, t->toPlainText());

            QComboBox *b = dynamic_cast<QComboBox *>(olParent->at(i));
            if((b)&&qmTable->contains(sObName))
                qmTable->insert(sObName, QString("%1").arg(b->model()->data(b->model()->index(b->currentIndex(), 0)).toUInt()));

            QRadioButton *r = dynamic_cast<QRadioButton *>(olParent->at(i));
            if((r)&&qmTable->contains(sObName))
            {
                QString rbStr="";
                rbStr = sObName.right(1);
                sObName = sObName.left(sObName.count()-1);
                if(r->isChecked())
                    qmTable->insert(sObName, rbStr);
            }
        }
    }
}

int basefill::findRecord(QSqlTableModel *tableModel, quint32 id)
{
    for(int i=0; i<tableModel->rowCount(); i++)
    {
        if(id == tableModel->index(i, 0).data(Qt::DisplayRole).toUInt())
            return i;
    }
    return (-1);
}

