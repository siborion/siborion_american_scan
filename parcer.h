#ifndef PARCER_H
#define PARCER_H

#include "typedef.h"
#include "curparam.h"
#include <QObject>

class Parcer : public QObject
{
    Q_OBJECT
public:
    explicit Parcer(QObject *parent = 0, CurParam *link=0);
    bool findExtremum(QByteArray *Sample, QList<quint16> &extremum);

private:
    CurParam *curParam;

signals:

public slots:

};

#endif // PARCER_H
