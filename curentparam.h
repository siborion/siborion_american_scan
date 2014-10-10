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

public:
    enum WorkRegim {regimAuto=0, regimAutoFreez=1, regimManual=2};
//    enum ItemDataRole{TypeRole = Qt::UserRole + 1000,
//                        SignalValueRole = Qt::UserRole + 1001};


    quint16 patientId, doctorId;    //
    quint16 corneaX1, corneaX2;     //
    quint16 lensX1,   lensX2;       //intervals
    quint16 retinaX1, retinaX2;     //
    bool cataract;                  //lens enabled
    bool contact;
    quint8 workRegim;

    void refreshPatientModel();
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
