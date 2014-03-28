#include "basefill.h"

basefill::basefill(QObject *parent) :
    QObject(parent)
{
    pBase = scanbase::instanse();

}

void basefill::fillData()
{
    QString str;
    QSqlQuery  query;
    QSqlRecord rec;
    QObjectList objectList;

    str = "select * from patient where id = %1 ;";
    str = str.arg(Id);
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
//                        if(sObName == "doctor")
//                            b->setCurrentIndex(findRecord(model, val));
                    }
                }
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

void basefill::save()
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
    strUpdate.append(QString(" where id=%1;").arg(Id));

    if(Id>0)
        query.prepare(strUpdate);
    else
        query.prepare(strInsertColumn);
    query.exec();
}
