#ifndef DIALOG_LENS_H
#define DIALOG_LENS_H

#include <QDialog>
#include "scanbase.h"
#include "basefill.h"


namespace Ui {
class dialog_lens;
}

class dialog_lens : public QDialog
{
    Q_OBJECT
    
public:
    explicit dialog_lens(quint32 id, QWidget *parent = 0);
    ~dialog_lens();
    
private:
    Ui::dialog_lens *ui;
    scanbase *pBase;
    basefill *pBaseFill;

private slots:
    void saveData();

};

#endif // DIALOG_LENS_H
