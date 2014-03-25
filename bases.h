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
#include <patient.h>
#include <doctor.h>
#include <lens.h>
#include <QPainter>
#include <QSql>
#include <QSqlQueryModel>
#include "scanbase.h"

namespace BaseType
{
    enum Status
    {
        enPatient = 0,
        enDoctor = 1,
        enLens = 2
    };
}

class bases : public QWidget
{
    Q_OBJECT
public:
    explicit bases(QWidget *parent = 0);

signals:

public slots:

private:
    scanbase *pBase;
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

private slots:
    void adjTable(BaseType::Status);
    void changeBasePatient(bool Val);
    void changeBaseDoctor(bool Val);
    void changeBaseLens(bool Val);
    void Add();
    void Edit();
    void Del();
};

#endif // BASES_H
