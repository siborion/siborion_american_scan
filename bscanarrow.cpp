#include "bscanarrow.h"

BScanArrow::BScanArrow(quint16 x, quint16 y)
{
    vertex.append(new BScanvertex(x,y));
}

BScanvertex *BScanArrow::findVertex(quint16 x, quint16 y)
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

BScanvertex *BScanArrow::addVertex(quint16 x, quint16 y)
{
    vertex.append(new BScanvertex(x,y));
    return vertex.last();
}



