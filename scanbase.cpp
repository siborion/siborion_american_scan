#include "scanbase.h"
scanbase *scanbase::_instanse = NULL;
scanbase::scanbase()
{
    QString sCurPath;
    sCurPath = QDir::currentPath();
    sCurPath.append("/base.db");
    pDB = QSqlDatabase::addDatabase("QSQLITE");
    pDB.setDatabaseName(sCurPath);

    QMessageBox msgBox;
//    msgBox.setText(sCurPath);
//    msgBox.exec();

    if(pDB.open())
    {
    }
    else
    {
        msgBox.setText("File not found");
        msgBox.exec();
    }
}

QSqlQuery scanbase::getData(QString str)
{
    QSqlQuery query;
    query.prepare(str);
    query.exec();
    return query;
}

