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
    bool side;

    CurentParam();
    static CurentParam *instanse()
    {
        if(_instanse == NULL)
            _instanse = new CurentParam();
        return _instanse;
    }
//    quint16 idPatient;
    QDataWidgetMapper patientMaper;
    QDataWidgetMapper measureParamMaper;
    void changePatient(quint16 idPatient);
    void changeSide();

private slots:
    void changeMaper(int num);
};

#endif // CURENTPARAM_H
