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

void Scanbase::getBasesModel(Base::TypeBase typeBase)
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
    qDebug()<<modelBases->rowCount();
    for(int i=0; i<lst.count(); i++)
    {
        modelBases->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
    }
    emit setBasesModel(modelBases);
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
    curPatient.id = id;
    if(id==0)
    {
        curPatient.name   = "New";
    }
    else
    {
        if(sql.exec())
        {
            if(sql.next())
            {
                curPatient.adress = sql.value(sql.record().indexOf("adress")).toString();
                curPatient.age    = sql.value(sql.record().indexOf("age")).toUInt();
                curPatient.birth  = sql.value(sql.record().indexOf("birth")).toDate();
                curPatient.doctor = sql.value(sql.record().indexOf("doctor")).toUInt();
                curPatient.k1left = sql.value(sql.record().indexOf("k1left")).toDouble();
                curPatient.k1right= sql.value(sql.record().indexOf("k1right")).toDouble();
                curPatient.k2left = sql.value(sql.record().indexOf("k2left")).toDouble();
                curPatient.k2right= sql.value(sql.record().indexOf("k2right")).toDouble();
                curPatient.kleft  = sql.value(sql.record().indexOf("kleft")).toDouble();
                curPatient.kright = sql.value(sql.record().indexOf("kright")).toDouble();
                curPatient.last   = sql.value(sql.record().indexOf("last")).toString();
                curPatient.name   = sql.value(sql.record().indexOf("name")).toString();
                curPatient.phone  = sql.value(sql.record().indexOf("phone")).toString();
                curPatient.ref    = sql.value(sql.record().indexOf("ref")).toString();
                curPatient.sex    = sql.value(sql.record().indexOf("sex")).toUInt();
                curPatient.state  = sql.value(sql.record().indexOf("state")).toString();
                curPatient.zip    = sql.value(sql.record().indexOf("zip")).toString();
            }
        }
    }
    emit (setStPatient(&curPatient));
}





