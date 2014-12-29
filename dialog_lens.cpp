#include "dialog_lens.h"
#include "ui_dialog_lens.h"

Dialog_Lens::Dialog_Lens(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Lens)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
}

Dialog_Lens::~Dialog_Lens()
{
    delete ui;
}

void Dialog_Lens::saveData()
{
//    pBaseFill->saveData();
    accept();
}
