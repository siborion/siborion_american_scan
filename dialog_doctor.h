#ifndef DIALOG_DOCTOR_H
#define DIALOG_DOCTOR_H

#include <QDialog>
#include "scanbase.h"
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include "combo_delegate.h"
#include "delegate.h"
#include "checkboxdelegate1.h"
#include "basefill.h"

namespace Ui {
class Dialog_Doctor;
}

class Dialog_Doctor : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Doctor(QMap <QString, QString> *stDoctor, QWidget *parent = 0);
    ~Dialog_Doctor();
    QMap<quint16,quint16> idLens;
    quint16 idDoc;

private:
    Ui::Dialog_Doctor *ui;
    QStandardItemModel  *model;
    basefill   *pBaseFill;

private slots:
    void saveData();
};

#endif // DIALOG_DOCTOR_H
