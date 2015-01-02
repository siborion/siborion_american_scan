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
                qDebug()<<sObName;
                if(qmTable->contains(sObName))
                {
                    qDebug()<<sObName;
                    qint8 recNum = qmTable->value(sObName,"").toInt();
                    qDebug()<<recNum;
//                    b->setCurrentIndex(1);
//                    qDebug()<<b->findData()
                }
            }
        }
    }
}

void basefill::saveData()
{
    QString strUpdate;
    QString strUpdateValue;
    QSqlQuery  query;
//    QSqlRecord rec;
    QString sObName;
    QString strInsertColumn;
    QString strInsertValue;

    strUpdate = QString("update %1 set id=id").arg(qsTableName);
    strInsertColumn = QString("insert into %1 (").arg(qsTableName);
    strInsertValue = " values (";

    for(int i=0; i<olParent->count();i++)
    {
        sObName = olParent->at(i)->objectName();

        if(sObName.left(3) == "VAL")
        {
            sObName = sObName.right(sObName.count()-3);
            strUpdateValue = "";

            QDateEdit *d = dynamic_cast<QDateEdit *>(olParent->at(i));
            if(d)
                strUpdateValue = d->text();

            QLineEdit *c = dynamic_cast<QLineEdit *>(olParent->at(i));
            if(c)
                strUpdateValue = c->text();

            QTextEdit *t = dynamic_cast<QTextEdit *>(olParent->at(i));
            if(t)
                strUpdateValue = t->toPlainText();

            QComboBox *b = dynamic_cast<QComboBox *>(olParent->at(i));
            if(b)
            {
                strUpdateValue = QString("%1").arg(b->model()->data(b->model()->index(b->currentIndex(), 0)).toUInt());
                qDebug()<<"strUpdateValue"<<strUpdateValue;
            }

            QRadioButton *r = dynamic_cast<QRadioButton *>(olParent->at(i));
            if(r)
            {
                QString rbStr="";
                rbStr = sObName.right(1);
                sObName = sObName.left(sObName.count()-1);
                if(r->isChecked())
                    strUpdateValue = rbStr;
            }

//            if(!strUpdateValue.isEmpty())
//            {
                strUpdate.append(QString(",\"%1\"='%2'").arg(sObName).arg(strUpdateValue));
                strInsertColumn.append(QString("\"%1\",").arg(sObName));
                strInsertValue.append(QString("'%1',").arg(strUpdateValue));
//            }
        }
    }
    strInsertColumn=strInsertColumn.mid(0,strInsertColumn.count()-1);
    strInsertColumn.append(") ");
    strInsertValue =strInsertValue.mid (0,strInsertValue.count()-1);
    strInsertValue.append(") ");
    strInsertColumn.append(strInsertValue);
    strUpdate.append(QString(" where id=%1;").arg(uiId));


    if(uiId>0)
    {
        query.prepare(strUpdate);
    }
    else
    {
        query.prepare(strInsertColumn);
    }
    query.exec();
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

