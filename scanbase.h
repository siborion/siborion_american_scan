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
#include "curparam.h"
#include "typedef.h"

class Scanbase : public QObject //QSqlDataguardbase
{
    Q_OBJECT
private:
    QSqlDatabase    pDB;
    CurParam *curParam;

public:
    explicit Scanbase(QObject *parent = 0, CurParam *link = 0);
    QSqlQuery getData(QString str);
    QSqlQueryModel *modelBases;
    QMap <QString, QString> curPatient;
    QMap <QString, QString> curDoctor;
    QMap <QString, QString> curLens;
    QSqlQueryModel lensModel;

public slots:
    void getBasesModel(Base::TypeBase, QSqlQueryModel**);

    void updateCurPatient(quint16);
    void saveCurPatient(quint16 *id);
    void delPatient();

    void updateCurDoctor(quint16);
    void saveCurDoctor(quint16 *id);
    void delDoctor();
    void saveDocLens(quint16 idDoc, QMap<quint16,quint16> *idLens);

    void updateCurLens(quint16);
    void saveCurLens(quint16 *id);
    void delLens();

    void saveSlot(QStandardItemModel *,QStandardItemModel *);
    void slSave(QStandardItemModel*, QStandardItemModel*, QStandardItemModel*); //bscan


Q_SIGNALS:
    void setBasesModel(QSqlQueryModel*);

    void setStPatient(QMap <QString, QString> *);
    void setStDoctor(QMap <QString, QString> *);
    void setStLens(QMap <QString, QString> *);
    void setLens(QSqlQueryModel*);
};

#endif // guardbase_H
