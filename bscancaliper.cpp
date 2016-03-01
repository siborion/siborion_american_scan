#include "bscancaliper.h"
#include <QDebug>

BScanCaliper::BScanCaliper(quint16 x, quint16 y)
{
        vertex.append(new BScanvertex(this, x,y));
}

BScanvertex *BScanCaliper::findVertex(quint16 x, quint16 y)
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

BScanvertex *BScanCaliper::addVertex(quint16 x, quint16 y)
{
    qDebug()<<"this"<<this;
    vertex.append(new BScanvertex(this,x,y));
    return vertex.last();
}



