#include "dialog_doctor.h"
#include "ui_dialog_doctor.h"

dialog_doctor::dialog_doctor(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_doctor)
{
    ui->setupUi(this);
    pBase = scanbase::instanse();
    pBaseFill = new basefill(id, children(), (QString)"doctor");
    pBaseFill->fillData();
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
}

dialog_doctor::~dialog_doctor()
{
    delete ui;
}

void dialog_doctor::saveData()
{
    pBaseFill->saveData();
    accept();
}
