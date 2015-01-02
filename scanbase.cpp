#include "scanbase.h"

Scanbase::Scanbase(QObject *parent)
{
    QString sCurPath;
    sCurPath = QDir::currentPath();
    sCurPath.append("/base.db");
    pDB = QSqlDatabase::addDatabase("QSQLITE");
    pDB.setDatabaseName(sCurPath);

    modelBases = new QSqlQueryModel();

    if(pDB.open())
    {

    }
    else
    {
//        msgBox.setText("File not found");
//        msgBox.exec();
    }


//    getBasesTable(Base::enPatient);

}

void Scanbase::getBasesModel(Base::TypeBase typeBase, QSqlQueryModel** model)
{
    QString str;
    QStringList lst;

    switch (typeBase)
    {
    case Base::enPatient:
        lst<<tr("Patient ID")<<tr("Name")<<tr("Doctor Name")<<tr("Notes");
        str = "SELECT id, name||' '||last as name, doctor, notes from v_patient;";
        break;
    case Base::enDoctor:
        lst             <<tr("Doctor Id") <<tr("First Name")<<tr("Last Name")<<tr("Notes");
        str = "SELECT id, name, last, note from doctor;";
        break;
    case Base::enLens:
        lst             <<tr("id") <<tr("Lens Name")<<tr("Mfg Name")<<tr("Mfg A_Const")<<tr("Mfg ACD")<<tr("Mfg SF")<<tr("Hoffer ACD");
        str = "SELECT id, name, mfg, aconst, acd, sf, hacd from lens;";
        break;
    }
    modelBases->setQuery(str);
    for(int i=0; i<lst.count(); i++)
    {
        modelBases->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
    }
    *model = modelBases;
}

QSqlQuery Scanbase::getData(QString str)
{
    QSqlQuery query;
    query.prepare(str);
    query.exec();
    return query;
}

void Scanbase::updateCurPatient(quint16 id)
{
    QString str = QString("SELECT * FROM patient WHERE id=%1;").arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        if(sql.next())
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curPatient[sql.record().fieldName(i)] = sql.record().value(i).toString();
            }
        }
        else
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curPatient[sql.record().fieldName(i)] = "";
            }
        }
    }
    emit (setStPatient(&curPatient));
}

void Scanbase::saveCurPatient(quint16 *id)
{
    QSqlQuery  query;
    QString sql;
    QString str;
    QString field, value;
    *id = 0;

    QMap<QString,QString>::iterator it = curPatient.begin();
    for(;it != curPatient.end(); ++it)
    {
        if(!(it.key() == "id"))
        {
            str.append(",");
            str.append(it.key());
            str.append("=");
            str.append('"');
            str.append(it.value());
            str.append('"');

            field.append(it.key());
            field.append(",");

            value.append('"');
            value.append(it.value());
            value.append('"');
            value.append(",");
        }
    }
    field.resize(field.length()-1);
    value.resize(value.length()-1);

    if(curPatient["id"].toInt()>0)
        sql.append(QString("update patient set id=id %1 where id=%2").arg(str).arg(curPatient["id"].toInt()));
    else
        sql.append(QString("insert into patient (%1) values (%2)").arg(field).arg(value));

    query.prepare(sql);
    query.exec();
}

void Scanbase::delPatient()
{
    QSqlQuery  query;
    QString sql;
    sql.append(QString("delete from patient where id=%1").arg(curPatient["id"].toInt()));
    query.prepare(sql);
    query.exec();
}






void Scanbase::updateCurDoctor(quint16 id)
{
    QString str = QString("SELECT * FROM doctor WHERE id=%1;").arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        if(sql.next())
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curDoctor[sql.record().fieldName(i)] = sql.record().value(i).toString();
            }
        }
        else
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curDoctor[sql.record().fieldName(i)] = "";
            }
        }
    }
    emit (setStDoctor(&curDoctor));
}

void Scanbase::saveCurDoctor(quint16 *id)
{
    QSqlQuery  query;
    QString sql;
    QString str;
    QString field, value;
    *id = 0;

    QMap<QString,QString>::iterator it = curDoctor.begin();
    for(;it != curDoctor.end(); ++it)
    {
        if(!(it.key() == "id"))
        {
            str.append(",");
            str.append(it.key());
            str.append("=");
            str.append('"');
            str.append(it.value());
            str.append('"');

            field.append(it.key());
            field.append(",");

            value.append('"');
            value.append(it.value());
            value.append('"');
            value.append(",");
        }
    }
    field.resize(field.length()-1);
    value.resize(value.length()-1);

    if(curDoctor["id"].toInt()>0)
        sql.append(QString("update doctor set id=id %1 where id=%2").arg(str).arg(curDoctor["id"].toInt()));
    else
        sql.append(QString("insert into doctor (%1) values (%2)").arg(field).arg(value));

    qDebug()<<sql;
    query.prepare(sql);
    query.exec();
}

void Scanbase::delDoctor()
{
    QSqlQuery  query;
    QString sql;
    sql.append(QString("delete from doctor where id=%1").arg(curDoctor["id"].toInt()));
    query.prepare(sql);
    query.exec();
}



