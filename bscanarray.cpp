#include "bscanarray.h"
#include <QDebug>

BScanArray::BScanArray(quint16 x, quint16 y)
{
        vertex.append(new BScanvertex(this, x,y));
}

BScanvertex *BScanArray::findVertex(quint16 x, quint16 y)
{
    BScanvertex *vxTmp;
    foreach (BScanvertex *vx, vertex)
    {
        vxTmp = vx->findVertex(x,y);
        if(vxTmp)
            return vxTmp;
    }
    return 0;
}

BScanvertex *BScanArray::addVertex(quint16 x, quint16 y)
{
    vertex.append(new BScanvertex(this,x,y));
    return vertex.last();
}

float BScanArray::getS()
{
    QList<float> Sum1, Sum2;
    float S1=0, S2=0;
    for(quint8 i=0; i<vertex.size(); i++)
    {
        quint8 next;
        next = ((i+1)==vertex.size()) ? 0 : (i+1);
        Sum1.append(vertex.at(i)->xKoord*vertex.at(next)->yKoord);
        Sum2.append(vertex.at(i)->yKoord*vertex.at(next)->xKoord);
    }

    foreach(float sm, Sum1)
    {
        S1 += sm;
    }

    foreach(float sm, Sum2)
    {
        S2 += sm;
    }

    return (S1-S2);
}

