#ifndef BSCANCALIPER_H
#define BSCANCALIPER_H
#include <QObject>
#include <bscanvertex.h>

class BScanCaliper: public QObject
{
     Q_OBJECT
public:
    BScanCaliper(quint16 x, quint16 y);
    QList<BScanvertex*> vertex;
    BScanvertex *findVertex(quint16 x, quint16 y);
    BScanvertex *addVertex(quint16 x, quint16 y);
};

#endif // BSCANCALIPER_H
