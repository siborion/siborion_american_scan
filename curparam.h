#ifndef CURPARAM_H
#define CURPARAM_H

#include <QObject>

enum RegimMeasure  {AUTOFREEZ, AUTO, MANUAL};
enum RegimContact  {CONTACT,   IMMERSION};
enum RegimCataract {CATARACT,  APHAKIC};
enum RegimSide     {OD, OS};

class CurParam : public QObject
{
    Q_OBJECT
public:
    explicit CurParam(QObject *parent = 0);

private:
    RegimMeasure  regimMeasure;
    RegimContact  regimContact;
    RegimCataract regimCataract;
    RegimSide     regimSide;

signals:

public slots:

};

#endif // CURPARAM_H
