#include "calclens.h"
#include "ui_calclens.h"

CalcLens::CalcLens(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CalcLens)
{
    ui->setupUi(this);
    gridLayout = new QGridLayout(this);
    QList<int>pr;
    pr<<0<<10<<10<<10<<10<<10<<10<<10<<10<<10<<10;
    QTableView tw;
    lensTable = new CalcLensTable (17, 11, pr, &tw);

    gridLayout->addWidget(lensTable);
}

void CalcLens::setValue(quint8 nomLens, quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal)
{
    lensTable->setValue(nomLens, formula, name, aconst, acd, fs, a0, a1, a2, dK, dAL, dACD, RxVal);
}

CalcLens::~CalcLens()
{
    delete ui;
}
