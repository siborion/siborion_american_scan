#ifndef DIALOG_DOCTOR_H
#define DIALOG_DOCTOR_H

#include <QDialog>
#include "scanbase.h"
#include "basefill.h"
#include "delegate.h"
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>

namespace Ui {
class dialog_doctor;
}

class dialog_doctor : public QDialog
{
    Q_OBJECT
    
public:
    explicit dialog_doctor(quint32 id, QWidget *parent = 0);
    ~dialog_doctor();
    
private:
    Ui::dialog_doctor *ui;
    scanbase *pBase;
    basefill *pBaseFill;
    QSqlQueryModel  *model;

private slots:
    void saveData();

};

#endif // DIALOG_DOCTOR_H
