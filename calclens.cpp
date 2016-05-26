#include "calclens.h"
#include "ui_calclens.h"

CalcLens::CalcLens(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CalcLens)
{
    ui->setupUi(this);
    gridLayout = new QGridLayout(this);
    QList<int>pr;
    pr<<14<<14<<14<<14<<14<<14<<14;
    QTableView tw;
    lensTable = new CalcLensTable (17, 7, pr, &tw);
    gridLayout->addWidget(lensTable);

}

CalcLens::~CalcLens()
{
    delete ui;
}
