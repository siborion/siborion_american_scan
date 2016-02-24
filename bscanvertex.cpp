#include "bscanvertex.h"
#include <QDebug>

BScanvertex::BScanvertex(quint16 x, quint16 y)
{
    xKoord = x;
    yKoord = y;
    edit = false;
}

BScanvertex *BScanvertex::findVertex(quint16 x, quint16 y)
{
    if((qAbs(x-xKoord)<10)&&(qAbs(y-yKoord)<10))
        return this;
    return 0;
}

bool BScanvertex::vertexEdit()
{
    return edit;
}
