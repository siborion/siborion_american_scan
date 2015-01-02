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
#include <QDateEdit>
#include "scanbase.h"
#include "basefill.h"
#include <QSqlTableModel>
#include <QStandardItem>

class Dialog_Patient : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog_Patient(QMap <QString, QString> *stPatient, QWidget *parent = 0);

private:
//    scanbase *pBase;
    basefill *pBaseFill;
    QSqlTableModel *model;
    quint32 patientId;
    void test (const QObjectList &t);

    QLineEdit  *leK1Left;
    QLineEdit  *leK1Right;
    QLineEdit  *leK2Left;
    QLineEdit  *leK2Right;
    QLineEdit  *leKLeft;
    QLineEdit  *leKRight;
    QLineEdit  *leAge;

signals:
public slots:

private slots:
    void saveData();
    void kLeftAverage();
    void kRightAverage();
    void calculateAge(QDate date);
};

#endif // PATIENT_H
