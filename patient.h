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


class patient : public QDialog
{
    Q_OBJECT
public:
    explicit patient(quint32 id, QWidget *parent = 0);

private:
    scanbase *pBase;

signals:

public slots:

};

#endif // PATIENT_H
