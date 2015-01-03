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
#include "typedef.h"
/*
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
*/

class Scanbase : public QObject //QSqlDataguardbase
{
    Q_OBJECT
private:
    QSqlDatabase    pDB;

public:
    explicit Scanbase(QObject *parent = 0);
    QSqlQuery getData(QString str);
    QSqlQueryModel *modelBases;
    QMap <QString, QString> curPatient;
    QMap <QString, QString> curDoctor;

public slots:
    void getBasesModel(Base::TypeBase, QSqlQueryModel**);

    void updateCurPatient(quint16);
    void saveCurPatient(quint16 *id);
    void delPatient();

    void updateCurDoctor(quint16);
    void saveCurDoctor(quint16 *id);
    void delDoctor();
    void saveDocLens(quint16 idDoc, QMap<quint16,quint16> *idLens);

Q_SIGNALS:
    void setBasesModel(QSqlQueryModel*);

    void setStPatient(QMap <QString, QString> *);
    void setStDoctor(QMap <QString, QString> *);
};

#endif // guardbase_H
