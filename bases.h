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
    qint16   numRowPatient;
    QMap <QString, QString> *stPatient;
    QMap <QString, QString> *stDoctor;
    QMap <QString, QString> *stLens;

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
    void setStDoctor(QMap <QString, QString> *stDoctorBases);
    void setStLens(QMap <QString, QString> *stDoctorLens);

Q_SIGNALS:
    void getModel(Base::TypeBase, QSqlQueryModel **);

    void updateCurPatient(quint16);
    void savePatient(quint16 *);
    void delPatient();

    void updateCurDoctor(quint16);
    void saveDoctor(quint16 *);
    void delDoctor();
    void saveDocLens(quint16 idDoc, QMap<quint16,quint16> *idLens);

    void updateCurLens(quint16);
    void saveLens(quint16 *);
    void delLens();


};

#endif // BASES_H
