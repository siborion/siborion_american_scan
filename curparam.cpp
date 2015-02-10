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

    regimMeasure = REGIM::AUTOFREEZ;
    regimContact = REGIM::CONTACT;
    regimCataract= REGIM::CATARACT;
    regimSide    = REGIM::OD;

    lensModel = new QSqlQueryModel();

    patientName = "Select Patient";
    doctorName  = "Select Doctor";
    doctorId = patientId = 0;

    ACD = ALave = K = k1left = k2left = k1right = k2right =0;
}
