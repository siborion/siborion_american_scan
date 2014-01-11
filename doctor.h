#ifndef DOCTOR_H
#define DOCTOR_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QStandardItemModel>
#include <adjview.h>

class doctor : public QDialog
{
    Q_OBJECT
public:
    explicit doctor(QWidget *parent = 0);
    QStandardItemModel *modelDoctor;
    QStandardItemModel *modelLens;
    QString baseMap[4][2] = {
        {"Doctor ID",  "doctorId"},
        {"First Name", "firstName"},
        {"Last Name",  "lastName"},
        {"Note_", "Note"}
        };

signals:

private:
    adjview *twDoctor;
    adjview *twLens;

public slots:

};


#endif // DOCTOR_H
