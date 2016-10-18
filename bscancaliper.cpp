#include "bscancaliper.h"
#include <QDebug>

BScanCaliper::BScanCaliper(quint16 x, quint16 y)
{
    vertex.append(new BScanvertex(this,x,y));
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
    vertex.append(new BScanvertex(this,x,y));
    return vertex.last();
}

float BScanCaliper::getLenght()
{
    float ret;
    ret = sqrt(pow(this->vertex.first()->xKoord - this->vertex.last()->xKoord , 2) + pow(this->vertex.first()->yKoord - this->vertex.last()->yKoord , 2));
    qDebug()<<"vertex.first()->xKoord"<<vertex.first()->xKoord;
    qDebug()<<"vertex.first()->yKoord"<<vertex.first()->yKoord;

    return ret;
}


