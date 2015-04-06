#ifndef PARSERFRONT_H
#define PARSERFRONT_H
#include <qglobal.h>

class parserFront
{

public:
    parserFront(quint16 start, quint16 end, quint8 front, quint8 zero, quint8 max);
    qint16 parser(quint16 pos, quint8 val);
private:
    quint16 intervalStart, intervalEnd, lenthFront;
    quint8 lenhtZero, maxZero;
    quint16 countZero;
    quint16 countFront;
    qint16 level60;
    bool extremum;
};

#endif // PARSERFRONT_H
