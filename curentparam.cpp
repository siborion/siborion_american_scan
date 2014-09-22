#include "curentparam.h"
#include <QDebug>
#include <QSqlQueryModel>

CurentParam *CurentParam::_instanse = NULL;
CurentParam::CurentParam()
{
    pBase = scanbase::instanse();
    patientMaper.setModel(&patientModel);
    lensModel = new QSqlQueryModel();
//    connect(&patientMaper, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMaper(int)));
}

void CurentParam::changeMaper(int num)
{
//    QAbstractItemModel  *model;
//    model = patientMaper.model();
//    qDebug() << model->data(model->index(num,1));
}

void CurentParam::changePatient(quint16 id)
{
    QString str;
    patientId = id;

//    str = "SELECT patient.id,";
//    str.append("patient.name||' '||patient.last as name,");
//    str.append("doc.name,");
//    str.append("patient.doctor as id_doctor,");
//    if(side==SIDE_LEFT)
//        str.append("patient.k1left as k1, patient.k2left as k2, 'OD' as side ");
//    else
//        str.append("patient.k1right as k1, patient.k2right as k2, 'OS' as side ");
//    str.append("FROM patient ");
//    str.append("LEFT JOIN doctor doc ON (doc.id = patient.doctor) ");
//    str.append(QString("where patient.id=%1;").arg(patientId));
//    qDebug()<<str;
//    patientModel.setQuery(str);
//    patientMaper.toFirst();

    refreshPatientModel();
    doctorId = patientModel.data(patientModel.index(0, 3)).toInt();

    str = "SELECT lens.name,";
    str.append("lens.aconst,");
    str.append("lens.acd,");
    str.append("lens.sf,");
    str.append("formula.id,");
    str.append("formula.name ");
    str.append("FROM patient, doctor_lens, lens, formula ");
    str.append("ON patient.doctor=doctor_lens.id_doctor ");
    str.append("AND lens.id=doctor_lens.id_lens ");
    str.append("AND doctor_lens.nom_formula=formula.id ");
    str.append(QString("WHERE patient.id=%1;").arg(patientId));
//    qDebug()<<str;
    lensModel->setQuery(str);
}

void CurentParam::changeSide()
{
    if(side)
        side = false;
    else
        side = true;

    refreshPatientModel();
//    qDebug()<<side;
}

void CurentParam::refreshPatientModel()
{
    QString str;
    str = "SELECT patient.id,";
    str.append("patient.name||' '||patient.last as name,");
    str.append("doc.name,");
    str.append("patient.doctor as id_doctor,");
    if(side==SIDE_LEFT)
        str.append("patient.k1left as k1,  patient.k2left as k2,  (patient.k1left+patient.k2left)/2 as k,   'OD' as side ");
    else
        str.append("patient.k1right as k1, patient.k2right as k2, (patient.k1right+patient.k2right)/2 as k, 'OS' as side ");
    str.append("FROM patient ");
    str.append("LEFT JOIN doctor doc ON (doc.id = patient.doctor) ");
    str.append(QString("where patient.id=%1;").arg(patientId));
    qDebug()<<str;
    patientModel.setQuery(str);
    patientMaper.toFirst();
}
