#include "bigviewnumhor.h"
#include <qDebug>

bigviewnumhor::bigviewnumhor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnumhor)
{
    ui->setupUi(this);
    setMinimumSize(200,200);
}

bigviewnumhor::~bigviewnumhor()
{
    delete ui;
}

void bigviewnumhor::setDisplay(double Al, double Avg, double Dev)
{
    ui->lAlCur->setText(QString("%1").arg(Al));
    ui->lAlAvg->setText(QString("%1").arg(Avg));
    ui->lAlDev->setText(QString("%1").arg(Dev));
}

void bigviewnumhor::setDisplay(double Al)
{
    ui->lAlCur->setText(QString("%1").arg(Al));
}
