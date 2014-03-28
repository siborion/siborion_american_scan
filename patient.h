#ifndef PATIENT_H
#define PATIENT_H

#include <QDialog>
#include <QRadioButton>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QFrame>
#include <QSpacerItem>
#include <QDebug>
#include "scanbase.h"
#include "basefill.h"
#include <QSqlTableModel>
#include <QStandardItem>

class patient : public QDialog
{
    Q_OBJECT
public:
    explicit patient(quint32 id, QWidget *parent = 0);

private:
    scanbase *pBase;
    basefill *pBaseFill;
    QSqlTableModel *model;
//    int findRecord(QSqlTableModel *tableModel, quint32 guid);
//    void fillData();
    quint32 patientId;
    void test (const QObjectList &t);

signals:
public slots:

private slots:
    void saveData();
};

#endif // PATIENT_H
