#include "lineselect.h"
#include "ui_lineselect.h"

LineSelect::LineSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineSelect)
{
    ui->setupUi(this);
}

LineSelect::~LineSelect()
{
    delete ui;
}
