#include "scanbase.h"
#include <QDateTime>
//#include <QtGlobal>

Scanbase::Scanbase(QObject *parent, CurParam *link)
{
    QString sCurPath;
    curParam = link;
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
            curPatient["id"]=QString("%1").arg(id);
            curParam->patientId   = id;
            curParam->doctorId    = curPatient.value("doctor").toUInt();
            curParam->patientName = curPatient.value("name")+" "+curPatient.value("last");
            curParam->k1left = curPatient.value("k1left").toDouble();
            curParam->k2left = curPatient.value("k2left").toDouble();
            curParam->k1right = curPatient.value("k1right").toDouble();
            curParam->k2right = curPatient.value("k2right").toDouble();
        }
        else
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curPatient[sql.record().fieldName(i)] = "";
            }
        }
    }

    str = QString("SELECT name, last FROM doctor WHERE id=%1;").arg(curParam->doctorId);
    if(sql.exec(str))
    {
        if(sql.next())
            curParam->doctorName = sql.record().value(0).toString()+" "+sql.record().value(1).toString();
    }

    emit (setStPatient(&curPatient));

    str = "SELECT lens.name,";
    str.append("lens.aconst,");
    str.append("lens.acd,");
    str.append("lens.sf,");
    str.append("formula.id,");
    str.append("formula.name ");
    str.append("FROM patient, doctor_lens, lens, formula ");
    str.append("ON patient.doctor=doctor_lens.id_doctor ");
    str.append("AND lens.id=doctor_lens.id_lens ");
    str.append("AND doctor_lens.nom_formula=formula.id ");
    str.append(QString("WHERE patient.id=%1;").arg(id));
    lensModel.setQuery(str);

    emit (setLens(&lensModel));
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
    curDoctor["id"]=QString("%1").arg(id);
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
    {
        sql.append(QString("update doctor set id=id %1 where id=%2").arg(str).arg(curDoctor["id"].toInt()));
        query.prepare(sql);
        query.exec();
        *id = curDoctor.value("id").toInt();
    }
    else
    {
        sql.append(QString("insert into doctor (%1) values (%2)").arg(field).arg(value));
        query.prepare(sql);
        query.exec();
        *id = query.lastInsertId().toInt();
    }
}

void Scanbase::delDoctor()
{
    QSqlQuery  query;
    QString sql;
    sql.append(QString("delete from doctor where id=%1").arg(curDoctor["id"].toInt()));
    query.prepare(sql);
    query.exec();
}

void Scanbase::saveDocLens(quint16 idDoc, QMap<quint16,quint16> *idLens)
{
    QString str;
    QSqlQuery sql(QString("DELETE FROM doctor_lens WHERE id_doctor=%1;").arg(idDoc));
    sql.exec();

    QMap<quint16,quint16>::iterator it = idLens->begin();
    for(;it != idLens->end(); ++it)
    {
    str = QString("INSERT INTO doctor_lens (id_lens, id_doctor, nom_formula) "
                  "VALUES (%1, %2, %3) ;")
          .arg(it.key()).arg(idDoc).arg(it.value());
    QSqlQuery sql;
    sql.exec(str);
    }
}




void Scanbase::updateCurLens(quint16 id)
{
    QString str = QString("SELECT * FROM lens WHERE id=%1;").arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        if(sql.next())
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curLens[sql.record().fieldName(i)] = sql.record().value(i).toString();
            }
        }
        else
        {
            for(int i=0; i<sql.record().count(); i++)
            {
                curLens[sql.record().fieldName(i)] = "";
            }
        }
    }
    curLens["id"]=QString("%1").arg(id);
    emit (setStLens(&curLens));
}

void Scanbase::saveCurLens(quint16 *id)
{
    QSqlQuery  query;
    QString sql;
    QString str;
    QString field, value;
    *id = 0;

    QMap<QString,QString>::iterator it = curLens.begin();
    for(;it != curLens.end(); ++it)
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

    if(curLens["id"].toInt()>0)
    {
        sql.append(QString("update lens set id=id %1 where id=%2").arg(str).arg(curLens["id"].toInt()));
        query.prepare(sql);
        query.exec();
        *id = curLens.value("id").toInt();
    }
    else
    {
        sql.append(QString("insert into lens (%1) values (%2)").arg(field).arg(value));
        query.prepare(sql);
        query.exec();
        *id = query.lastInsertId().toInt();
    }
}

void Scanbase::delLens()
{
    QSqlQuery  query;
    QString sql;
    sql.append(QString("delete from lens where id=%1").arg(curLens["id"].toInt()));
    query.prepare(sql);
    query.exec();
}

void Scanbase::saveSlot(QStandardItemModel *OD, QStandardItemModel *OS)
{
    QSqlQuery   query;
    QString     sql;
    quint16     rowCount;
    QModelIndex index;
    quint64 session;
    QDateTime session_time;

    session = qrand();
    session_time = QDateTime::currentDateTime();

    rowCount = OD->rowCount();
    for(quint16 i=0; i<rowCount; i++)
    {

        sql = "insert into history (";
        sql += "acd,";
        sql += "al,";
        sql += "al_ave,";
        sql += "cornea,";
        sql += "l1,";
        sql += "l2,";
        sql += "lt,";
        sql += "nom,";
        sql += "retina,";
        sql += "sample,";
        sql += "vit,";
        sql += "patient,";
        sql += "session,";
        sql += "session_time,";
        sql += "regim_side";
        sql += ") ";

        sql += "values (";
        sql += ":acd,";
        sql += ":al,";
        sql += ":al_ave,";
        sql += ":cornea,";
        sql += ":l1,";
        sql += ":l2,";
        sql += ":lt,";
        sql += ":nom,";
        sql += ":retina,";
        sql += ":sample,";
        sql += ":vit,";
        sql += ":patient,";
        sql += ":session,";
        sql += ":session_time,";
        sql += ":regim_side";
        sql += ")";
        query.prepare(sql);

        index = OD->index(i,0);
        query.bindValue(":cornea", OD->data(index,roleCornea).toUInt());
        query.bindValue(":l1",     OD->data(index,roleL1).toUInt());
        query.bindValue(":l2",     OD->data(index,roleL2).toUInt());
        query.bindValue(":retina", OD->data(index,roleRetina).toUInt());
        query.bindValue(":sample", OD->data(index,roleSample).toByteArray());
        query.bindValue(":nom",    OD->data(index,Qt::DisplayRole).toUInt());
        index = OD->index(i,1);
        query.bindValue(":al_ave", OD->data(index,Qt::DisplayRole).toDouble());
        index = OD->index(i,2);
        query.bindValue(":al", OD->data(index,Qt::DisplayRole).toDouble());
        index = OD->index(i,3);
        query.bindValue(":acd", OD->data(index,Qt::DisplayRole).toDouble());
        index = OD->index(i,4);
        query.bindValue(":lt", OD->data(index,Qt::DisplayRole).toDouble());
        index = OD->index(i,5);
        query.bindValue(":vit", OD->data(index,Qt::DisplayRole).toDouble());
        query.bindValue(":patient", curParam->patientId);
        query.bindValue(":session", session);
        query.bindValue(":session_time", session_time);
        query.bindValue(":regim_side", curParam->regimSide);
        query.exec();
    }
}


