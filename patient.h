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

class patient : public QDialog
{
    Q_OBJECT
public:
    explicit patient(QWidget *parent = 0);

signals:

public slots:

};

#endif // PATIENT_H
