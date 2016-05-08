#include "bscantext.h"

BScanText::BScanText(quint16 x, quint16 y)
{
    vertex = (new BScanvertex(this,x,y));
    text = "";
}

BScanvertex *BScanText::findVertex(quint16 x, quint16 y)
{
    BScanvertex *vxTmp;
    vxTmp = vertex->findVertex(x,y);
    if(vxTmp)
        return vxTmp;
    return 0;
}

BScanvertex *BScanText::addVertex(quint16 x, quint16 y)
{
//    vertex.append(new BScanvertex(this,x,y));
//    return vertex.last();
}


