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
    qDebug()<<modelBases->rowCount();
    for(int i=0; i<lst.count(); i++)
    {
        modelBases->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
    }
//    emit setBasesModel(modelBases);
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
//    curPatient.id = id;
    if(sql.exec())
    {
        if(sql.next())
        {
            for(uint i=0; i<sql.record().count(); i++)
            {
                curPatient[sql.record().fieldName(i)] = sql.record().value(i).toString();
            }
        }
    }
    emit (setStPatient(&curPatient));
}





