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

void BScanTools::on_pbStop_clicked()
{
    emit doStop();
    qDebug()<<"doStop";
}

void BScanTools::on_pbOS_clicked()
{
    emit doOS();
}

void BScanTools::setFps(quint8 val)
{
    ui->lFPS->setText(QString("FPS:%1").arg(val));
}

BScanTools::~BScanTools()
{
    delete ui;
}
