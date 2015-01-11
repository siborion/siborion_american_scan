#include "curparam.h"

CurParam::CurParam(QObject *parent) :
    QObject(parent)
{
    corneaX1 = 0;
    corneaX2 = 100;

    lensX1 = 200;
    lensX2 = 300;

    retinaX1 = 400;
    retinaX2 = 500;
}
