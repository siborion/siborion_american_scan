#ifndef TYPEDEF_H
#define TYPEDEF_H

struct stPatientParam
{
    quint16 id;
    float K;
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


#endif // TYPEDEF_H

