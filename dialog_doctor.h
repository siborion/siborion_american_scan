#ifndef DIALOG_DOCTOR_H
#define DIALOG_DOCTOR_H

#include <QDialog>
#include "scanbase.h"
#include "basefill.h"
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include "combo_delegate.h"
#include "delegate.h"

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
    QStandardItemModel  *model;
//    CheckBoxDelegate *delegate;
    quint32 curId;

private slots:
    void saveData();
    void include(bool);
    void changeModel(QModelIndex);
    void selectFormula();
};

#endif // DIALOG_DOCTOR_H
