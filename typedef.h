#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QObject>
namespace Base
{
    enum TypeBase
    {
        enPatient = 0,
        enDoctor = 1,
        enLens = 2
    };
}

namespace REGIM
{
enum RegimMeasure  {AUTOFREEZ, AUTO, MANUAL};
enum RegimContact  {CONTACT,   IMMERSION};
enum RegimCataract {CATARACT,  APHAKIC};
enum RegimSide     {OD, OS};
}

struct stMeasureParam
{
    QByteArray Sample;
    quint16 Cornea;
    quint16 L1;
    quint16 L2;
    quint16 Retina;
    double ALave;
    double AL;
    double ACD;
    double LT;
    double VIT;
    QList<quint16> extremum;
};

struct stAverageParam
{
    double AL;
    double ACD;
    double LT;
    double VIT;
    double ALdiv;
    double ACDdiv;
    double LTdiv;
    double VITdiv;
};

#define roleSample   Qt::UserRole+1
#define roleCornea   Qt::UserRole+2
#define roleL1       Qt::UserRole+3
#define roleL2       Qt::UserRole+4
#define roleRetina   Qt::UserRole+5
#define roleExtremum Qt::UserRole+6

#endif // TYPEDEF_H
