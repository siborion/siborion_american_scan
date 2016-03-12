#ifndef BSCANARRAY_H
#define BSCANARRAY_H
#include <QObject>
#include <bscanvertex.h>

class BScanArray: public QObject
{
     Q_OBJECT
public:
    BScanArray(quint16 x, quint16 y);
    QList<BScanvertex*> vertex;
    BScanvertex *findVertex(quint16 x, quint16 y);
    BScanvertex *addVertex(quint16 x, quint16 y);
};

#endif // BSCANARRAY_H
