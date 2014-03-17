#include "bigviewnum.h"
#include "ui_bigviewnum.h"
#include <qDebug>

bigviewnum::bigviewnum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnum)
{
    ui->setupUi(this);
    setMinimumSize(200,200);
}

bigviewnum::~bigviewnum()
{
    delete ui;
}

void bigviewnum::setDisplay(double Avg, double Dev)
{
    ui->lAlAvg->setText(QString("%1").arg(Avg));
    ui->lAlDev->setText(QString("%1").arg(Dev));
    qDebug() << "111";
}
