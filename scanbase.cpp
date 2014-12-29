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

    StPatient  curPatient;
    StDoctor   curDoctor;
    StLens     curLensl;

}

void Scanbase::getBasesTable(QString str)
{
//    qDebug()<<str;
//    modelBases = (QSqlQueryModel)pDB.exec(str);
    modelBases->setQuery(str);
//    qDebug()<<modelBases->rowCount();
    emit setModel(modelBases);
}

QSqlQuery Scanbase::getData(QString str)
{
    QSqlQuery query;
    query.prepare(str);
    query.exec();
    return query;
}

