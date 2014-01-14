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

enum {enPatient, enDoctor, enLens};

class bases : public QWidget
{
    Q_OBJECT
public:
    explicit bases(QWidget *parent = 0);

signals:

public slots:

private:
    void adjCol();

    adjview *twTable;
    QPushButton *pbAdd;
    QPushButton *pbDel;
    QPushButton *pbEdit;
    QPushButton *pbPatientHistory;
    QStandardItemModel *model;
    quint8 TypeBase;

private slots:
    void adjTable(quint8);
    void changeBasePatient(bool Val);
    void changeBaseDoctor(bool Val);
    void changeBaseLens(bool Val);
    void Add();
    void Edit();
    void Del();

};

#endif // BASES_H
