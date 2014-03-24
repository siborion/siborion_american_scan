#include "scanbase.h"
scanbase *scanbase::_instanse = NULL;
scanbase::scanbase()
{
    pDB = QSqlDatabase::addDatabase("QSQLITE");
    pDB.setDatabaseName("base.db");
    if(pDB.open())
    {
        qDebug() << "Open";
    }
}

QSqlQuery scanbase::getData(QString str)
{
    QSqlQuery query;
    query.prepare(str);
    query.exec();
    return query;
}

