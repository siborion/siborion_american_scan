#include "curentparam.h"
#include <QDebug>
#include <QSqlQueryModel>

CurentParam *CurentParam::_instanse = NULL;
CurentParam::CurentParam()
{
    pBase = scanbase::instanse();

    patientMaper.setModel(&patientModel);
    lensModel = new QSqlQueryModel();
    this->measureAveACD = this->measureAveAL = 0;
    sideOD = false;
    cataract = true;
    contact = true;
}

void CurentParam::changeMaper(int num)
{
//    QAbstractItemModel  *model;
//    model = patientMaper.model();
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
    lensModel->setQuery(str);

}

void CurentParam::changeSide()
{
    if(sideOD)
        sideOD = false;
    else
        sideOD = true;

    refreshPatientModel();


//    QString TTT = QString("%1").arg(10,4,'f',2);
//    QStandardItem item1;
//    item1.setData(TTT,Qt::DisplayRole);
//    measureParamModel.setItem(0,0,&item1);
//    QStandardItem item2;
//    item2.setData(TTT,Qt::DisplayRole);
//    measureParamModel.setItem(0,1,&item2);
//    measureParamMaper.toFirst();
}

void CurentParam::refreshPatientModel()
{
    QString str;

    emit changeSideSignal();

    str = "SELECT patient.id,";
    str.append("patient.name||' '||patient.last as name,");
    str.append("doc.name,");
    str.append("patient.doctor as id_doctor,");
    if(sideOD==true)
        str.append("patient.k1left as k1,  patient.k2left as k2,  (patient.k1left+patient.k2left)/2 as k,   'OD' as side ");
    else
        str.append("patient.k1right as k1, patient.k2right as k2, (patient.k1right+patient.k2right)/2 as k, 'OS' as side ");
    str.append("FROM patient ");
    str.append("LEFT JOIN doctor doc ON (doc.id = patient.doctor) ");
    str.append(QString("where patient.id=%1;").arg(patientId));
    patientModel.setQuery(str);
    patientMaper.toFirst();
}
