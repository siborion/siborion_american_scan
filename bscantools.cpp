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
    ui->gbAnnotation->setEnabled(false);
    emit doScan();
}

void BScanTools::on_pbStop_clicked()
{
    ui->gbAnnotation->setEnabled(true);
    emit doStop();
}

void BScanTools::on_pbOS_clicked()
{
    if(ui->pbOS->text()=="OS")
        ui->pbOS->setText("OD");
    else
        ui->pbOS->setText("OS");
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

void BScanTools::on_pbArray_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbArray);
    emit doEdit(CUR_EDIT::ARRAY, ui->pbArray->isChecked());
}

void BScanTools::on_pbCaliper_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbCaliper);
    emit doEdit(CUR_EDIT::CALIPER, ui->pbCaliper->isChecked());
}

void BScanTools::on_pbArrow_clicked()
{
    rechecketPb(ui->gbAnnotation, ui->pbArrow);
    emit doEdit(CUR_EDIT::ARROW, ui->pbArrow->isChecked());
}

BScanTools::~BScanTools()
{
    delete ui;
}
