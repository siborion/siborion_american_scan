#include "bscanvertex.h"

BScanvertex::BScanvertex(quint16 x, quint16 y)
{
    xKoord = x;
    yKoord = y;
    edit = false;
}

BScanvertex *BScanvertex::findVertex(quint16 x, quint16 y)
{
    return this;
    return 0;
}

bool BScanvertex::vertexEdit()
{
    return edit;
}
