#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QStandardItemModel>

struct stMainParam
{
    quint16 Start;
    quint16 L1;
    quint16 L2;
    quint16 Retina;
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

struct stMeasureParam
{
    float AL;
    float ACD;
};

struct stPersonalParam
{
    float AConst;
    float ACD;
    float SF;
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


struct stFormulaInfo
{
    QStandardItemModel *model;
    QString formulaName;
    QString lensName;
    QString IOL;
};

enum RegimMeasure  {AUTOFREEZ, AUTO, MANUAL};
enum RegimContact  {CONTACT,   IMMERSION};
enum RegimCataract {CATARACT,  APHAKIC};
enum RegimSide     {OD, OS};

#endif // TYPEDEF_H

