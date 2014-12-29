#ifndef DIALOG_DOCTOR_H
#define DIALOG_DOCTOR_H

#include <QDialog>
#include "scanbase.h"
#include "basefill.h"
#include <QStandardItemModel>
#include <QSqlRelationalTableModel>
#include "combo_delegate.h"
#include "delegate.h"
#include "checkboxdelegate1.h"

namespace Ui {
class Dialog_Doctor;
}

class Dialog_Doctor : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Doctor(quint32 id, QWidget *parent = 0);
    ~Dialog_Doctor();
    
private:
    Ui::Dialog_Doctor *ui;
//    scanbase *pBase;
    basefill *pBaseFill;
    QStandardItemModel  *model;
//    CheckBoxDelegate *delegate;
    quint32 curId;
//    void changeModel(QModelIndex index);

private slots:
    void saveData();
//    void include(bool);
//    void changeModel(QModelIndex);
//    void selectFormula();
};

#endif // DIALOG_DOCTOR_H
