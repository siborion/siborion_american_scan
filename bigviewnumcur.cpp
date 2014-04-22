#include "bigviewnumcur.h"
#include "ui_bigviewnumcur.h"
#include <qDebug>

bigviewnumcur::bigviewnumcur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigviewnumcur)
{
    ui->setupUi(this);
    setMinimumSize(200,200);
}

bigviewnumcur::~bigviewnumcur()
{
    delete ui;
}

void bigviewnumcur::setDisplay(double AL, double ACD, double LT, double VIT)
{
    ui->lCurAL->setText(QString("%1").arg(AL,4,'f',2));
    ui->lCurACD->setText(QString("%1").arg(ACD,4,'f',2));
    ui->lCurLT->setText(QString("%1").arg(LT,4,'f',2));
    ui->lCurVIT->setText(QString("%1").arg(VIT,4,'f',2));
}
