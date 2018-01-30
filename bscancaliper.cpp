#include "bscancaliper.h"
#include <QDebug>

BScanCaliper::BScanCaliper(quint16 x, quint16 y)
{
    vertex.append(new BScanvertex(this,x,y));
    qDebug()<<"0"<<x<<y<<vertex.length();
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
    qDebug()<<"1"<<x<<y<<vertex.length();
    return vertex.last();
}

float BScanCaliper::getLenght()
{
    float ret, x, y;

    x = this->vertex.first()->xKoord;
    y = this->vertex.first()->yKoord;
    ret = 0;

    foreach (BScanvertex *var, this->vertex)
    {
        if(var!=this->vertex.last())
        {
            qDebug()<<var->xKoord;
            ret += sqrt(pow(x - var->xKoord , 2) + pow(y - var->yKoord , 2));
        }
        else
        {
            qDebug()<<"last";
            qDebug()<<var->xKoord;
        }
        x = var->xKoord;
        y = var->yKoord;
    }
    return ret;
}


