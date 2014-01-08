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

signals:

private:
    adjview *twDoctor;
    QStandardItemModel *modelDoctor;
    adjview *twLens;
    QStandardItemModel *modelLens;

public slots:

};

#endif // DOCTOR_H
