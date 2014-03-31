#include "dialog_lens.h"
#include "ui_dialog_lens.h"

dialog_lens::dialog_lens(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_lens)
{
    ui->setupUi(this);
    pBase = scanbase::instanse();
    pBaseFill = new basefill(id, children(), (QString)"lens");
    pBaseFill->fillData();
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
}

dialog_lens::~dialog_lens()
{
    delete ui;
}

void dialog_lens::saveData()
{
    pBaseFill->saveData();
    accept();
}
