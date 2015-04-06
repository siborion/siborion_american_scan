#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QObject>
#include <QStandardItemModel>

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

struct stMainParam
{
    quint16 Start;
    quint16 L1;
    quint16 L2;
    quint16 Retina;
};

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
    double ALave;
    double ACD;
    double LT;
    double VIT;
    double ALavediv;
    double ACDdiv;
    double LTdiv;
    double VITdiv;
};

struct stFormulaInfo
{
    QStandardItemModel *model;
    QString formulaName;
    QString lensName;
    QString IOL;
};

struct stPatientParam
{
    quint16 id;
    QString Name;
    QString BirthDay;
    float K;
    float K1Left, K1Right;
    float K2Left, K2Right;
    float AL;
    float ACD;
};

struct stPersonalParam
{
    float AConst;
    float ACD;
    float SF;
    float Rx;
};

struct stPrintSample
{
    QByteArray sample1;
    QByteArray sample2;
    QByteArray sample3;
    stMainParam mainParam1;
    stMainParam mainParam2;
    stMainParam mainParam3;
};

#define roleSample   Qt::UserRole+1
#define roleCornea   Qt::UserRole+2
#define roleL1       Qt::UserRole+3
#define roleL2       Qt::UserRole+4
#define roleRetina   Qt::UserRole+5
#define roleExtremum Qt::UserRole+6

#endif // TYPEDEF_H
