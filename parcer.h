#ifndef PARCER_H
#define PARCER_H

#include "typedef.h"
#include "curparam.h"
#include "parserfront.h"
#include <QObject>

class Parcer : public QObject
{
    Q_OBJECT
public:
    explicit Parcer(QObject *parent = 0, CurParam *link=0);
    bool findExtremum(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam*);

private:
    CurParam *curParam;
    parserFront *parseCornea;
    parserFront *parseLens;
    parserFront *parseRetina;
    double decRound(double Val, quint8 dec, quint16 speed);

signals:

public slots:
    void calculateParam(stMeasureParam *measureParam);

};

#endif // PARCER_H
