#include "dialogserial.h"
#include "ui_dialogserial.h"

DialogSerial::DialogSerial(QWidget *parent, QStringList *lsName) :
    QDialog(parent),
    ui(new Ui::DialogSerial)
{
    ui->setupUi(this);
    cbPort = new QComboBox(this);
    cbPort->addItems(*lsName);

}

DialogSerial::~DialogSerial()
{
    delete ui;
}
