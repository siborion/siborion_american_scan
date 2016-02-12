#include "bscantools.h"
#include "ui_bscantools.h"

BScanTools::BScanTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanTools)
{
    ui->setupUi(this);
}

BScanTools::~BScanTools()
{
    delete ui;
}
