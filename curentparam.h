#ifndef CURENTPARAM_H
#define CURENTPARAM_H
#include "scanbase.h"
#include <QObject>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QStandardItemModel>

#define SIDE_LEFT 0

class CurentParam : public QObject
{
    Q_OBJECT
private:
    static CurentParam *_instanse;
    scanbase *pBase;
    QSqlQueryModel patientModel;
    QStandardItemModel measureParamModel;
    void refreshPatientModel();
    quint16 patientId, doctorId;

public:
    QSqlQueryModel *lensModel;
    bool sideOD;

    CurentParam();
    static CurentParam *instanse()
    {
        if(_instanse == NULL)
            _instanse = new CurentParam();
        return _instanse;
    }
//    quint16 idPatient;
    QDataWidgetMapper patientMaper;
//    QDataWidgetMapper measureParamMaper;
    void changePatient(quint16 idPatient);
    void changeSide();
    double measureAveAL;
    double measureAveACD;
    double measureAveLT;
    double measureAveVIT;
    double measureDevAL;
    double measureDevACD;
    double measureDevLT;
    double measureDevVIT;


private slots:
    void changeMaper(int num);

Q_SIGNALS:
    void changeSideSignal();
};

#endif // CURENTPARAM_H
