#ifndef guardbase_H
#define guardbase_H

#include <QSqlError>
#include <iostream>
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

class scanbase : public QObject //QSqlDataguardbase
{
    Q_OBJECT
private:
    QSqlDatabase pDB;
    static scanbase *_instanse;

public:
    scanbase();
    static scanbase *instanse(){
        if(_instanse == NULL) _instanse = new scanbase();
        return _instanse;
    }
    QSqlQuery getData(QString str);
};

#endif // guardbase_H
