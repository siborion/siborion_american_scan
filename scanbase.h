#ifndef guardbase_H
#define guardbase_H

#include <QSqlError>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QMessageBox>
#include <QDate>

struct StPatient
{
    quint16 id;
    QString adress;
    quint8  age;
    QDate   birth;
    quint16 doctor;
    double k1left;
    double k1right;
    double k2left;
    double k2right;
    double kleft;
    double kright;
    QString last;
    QString name;
    QString phone;
    QString ref;
    quint8 sex;
    QString state;
    QString zip;
};

struct StDoctor
{
};

struct StLens
{
};


class Scanbase : public QObject //QSqlDataguardbase
{
    Q_OBJECT
private:
    QSqlDatabase    pDB;
    QSqlQueryModel *modelBases;

public:
    explicit Scanbase(QObject *parent = 0);
    QSqlQuery getData(QString str);

public slots:
    void getBasesTable(QString);

Q_SIGNALS:
    void setModel(QSqlQueryModel*);

};

#endif // guardbase_H
