#ifndef BASES_H
#define BASES_H

#include <QWidget>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QResizeEvent>
#include <adjview.h>
#include <QPainter>
#include <QSql>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>
#include <QGroupBox>
#include <QRadioButton>
#include "dialog_lens.h"
#include "dialog_doctor.h"
#include "dialog_patient.h"


namespace BaseType
{
    enum Status
    {
        enPatient = 0,
        enDoctor = 1,
        enLens = 2
    };
}

class Bases : public QWidget
{
    Q_OBJECT
public:
    explicit Bases(QWidget *parent = 0);

signals:

private:
    void adjCol();
    void fillModelHead(QStringList sl);
    adjview *twTable;
    QPushButton *pTest;
    QPushButton *pbAdd;
    QPushButton *pbDel;
    QPushButton *pbEdit;
    QPushButton *pbPatientHistory;
    QSqlQueryModel  *model;
    BaseType::Status TypeBase;
    QString *svg;
    QLabel    *lSearch;
    QLineEdit *leSearch;
    QModelIndex curPatient;

private slots:
    void adjTable(BaseType::Status);
    void changeBasePatient(bool Val);
    void changeBaseDoctor(bool Val);
    void changeBaseLens(bool Val);
    void Add();
    void Edit();
    void Del();
    void EditIndex(QModelIndex);
    void changeRow(QModelIndex cur, QModelIndex prev);

public slots:
    void setModel(QSqlQueryModel *modelBases);


Q_SIGNALS:
//    void changeRow(quint8 idType, quint16 idRow, QString Patient, QString Doctor);
    void getBasesTable(QString str);
};

#endif // BASES_H
