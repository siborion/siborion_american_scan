#ifndef CURPARAM_H
#define CURPARAM_H

#include <QObject>
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

    quint16 Start;
    quint16 L1;
    quint16 L2;
    quint16 Retina;

private:

signals:

public slots:

};

#endif // CURPARAM_H
