#include "curentparam.h"
#include <QDebug>
#include <QSqlQueryModel>

CurentParam *CurentParam::_instanse = NULL;
CurentParam::CurentParam()
{
    connect(&maper, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMaper(int)));
}

void CurentParam::changeMaper(int num)
{
    QAbstractItemModel  *model;
    model = maper.model();
    qDebug() << model->data(model->index(num,2));
}

