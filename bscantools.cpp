#include "bscantools.h"
#include "ui_bscantools.h"
#include <QDebug>

BScanTools::BScanTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanTools)
{
    ui->setupUi(this);
}

void BScanTools::on_pbScan_clicked()
{
    emit doScan();
}

void BScanTools::on_pbStop_clicked()
{
    emit doStop();
}

void BScanTools::on_pbOS_clicked()
{
    emit doOS();
}

void BScanTools::setFps(quint8 val)
{
    ui->lFPS->setText(QString("FPS:%1").arg(val));
}

void BScanTools::rechecketPb(QGroupBox *gb, QPushButton *pb)
{
    QObjectList ol;
    QObject *ob;
    ol = gb->children();
    foreach (ob, ol)
    {
        QPushButton *d = dynamic_cast<QPushButton*>(ob);
        if(d)
        {
            if(d!=pb)
                d->setChecked(false);
        }
    }
}

void BScanTools::on_pbClear_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbClear);
}

void BScanTools::on_pbText_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbText);
}

void BScanTools::on_pbCallper_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbCallper);
}

void BScanTools::on_pbAngle_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbAngle);
}

void BScanTools::on_pbArrow_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbArrow);
}

BScanTools::~BScanTools()
{
    delete ui;
}
