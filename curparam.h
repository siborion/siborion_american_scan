#ifndef CURPARAM_H
#define CURPARAM_H

#include <QObject>
#include <QSqlQueryModel>
#include "curparam.h"
#include "typedef.h"

class CurParam : public QObject
{
    Q_OBJECT
public:
    explicit CurParam(QObject *parent = 0);
    REGIM::RegimMeasure  regimMeasure;
    REGIM::RegimContact  regimContact;
    REGIM::RegimCataract regimCataract;
    REGIM::RegimSide     regimSide;

    quint16 corneaX1;
    quint16 corneaX2;
    quint16 lensX1;
    quint16 lensX2;
    quint16 retinaX1;
    quint16 retinaX2;

    quint64 randSession;

    QSqlQueryModel *lensModel;

    quint16 patientId;
    quint16 doctorId;
    QString patientName;
    QString doctorName;
    double k1left;
    double k2left;
    double k1right;
    double k2right;
    double AL;
    double ACD;


//    quint16 Start;
//    quint16 L1;
//    quint16 L2;
//    quint16 Retina;

//    stMeasureParam measureParam;

//    double ALave;
//    double AL;
//    double ACD;
//    double LT;
//    double Vit;

private:

signals:

public slots:

signals:
    void change();

};

#endif // CURPARAM_H
