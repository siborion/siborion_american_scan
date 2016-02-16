#include "bscantools.h"
#include "ui_bscantools.h"
#include <QDebug>

BScanTools::BScanTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanTools)
{
    ui->setupUi(this);
//    connect(ui->pbScan,SLOT(click()),
}

void BScanTools::on_pbScan_clicked()
{
    emit doScan();
    qDebug()<<"doScan";
}


BScanTools::~BScanTools()
{
    delete ui;
}
