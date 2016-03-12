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



