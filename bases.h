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
#include "typedef.h"
#include "scanbase.h"

class Bases : public QWidget
{
    Q_OBJECT
public:
    explicit Bases(QWidget *parent = 0);
    void Init();
signals:

private:
    QSqlQueryModel  *model;
    void adjCol();
    adjview *twTable;
    QPushButton *pTest;
    QPushButton *pbAdd;
    QPushButton *pbDel;
    QPushButton *pbEdit;
    QPushButton *pbPatientHistory;
    Base::TypeBase  typeBase;
    QString *svg;
    QLabel    *lSearch;
    QLineEdit *leSearch;
    quint16   numRowPatient;
    QMap <QString, QString> *stPatient;

private slots:
    void adjTable();
    void changeBase(bool Val);
    void Add();
    void Edit();
    void Del();
    void EditIndex(QModelIndex);
    void changeRow(QModelIndex cur, QModelIndex prev);

public slots:
//    void setModel(QSqlQueryModel *modelBases);
    void setStPatient(QMap <QString, QString> *stPatientBases);

Q_SIGNALS:
    void getModel(Base::TypeBase, QSqlQueryModel **);
    void updateCurPatient(quint16);
};

#endif // BASES_H
