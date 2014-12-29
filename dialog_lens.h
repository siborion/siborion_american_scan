#ifndef DIALOG_LENS_H
#define DIALOG_LENS_H

#include <QDialog>
#include "scanbase.h"
//#include "basefill.h"


namespace Ui {
class Dialog_Lens;
}

class Dialog_Lens : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Lens(quint32 id, QWidget *parent = 0);
    ~Dialog_Lens();
    
private:
    Ui::Dialog_Lens *ui;
//    scanbase *pBase;
//    basefill *pBaseFill;

private slots:
    void saveData();

};

#endif // DIALOG_LENS_H
