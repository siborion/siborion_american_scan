#include "bscanarrow.h"

BScanArrow::BScanArrow(quint16 x, quint16 y)
{
    start = new BScanvertex(x,y);
    end = new BScanvertex(x,y);
    editStart = editEnd = false;
}

void BScanArrow::setEnd(quint16 x, quint16 y)
{
    end->xKoord = x;
    end->yKoord = y;
}

quint16 BScanArrow::getXStart()
{
    return start->xKoord;
}

quint16 BScanArrow::getYStart()
{
    return start->yKoord;
}

quint16 BScanArrow::getXEnd()
{
    return end->xKoord;
}

quint16 BScanArrow::getYEnd()
{
    return end->yKoord;
}

arrow_edit BScanArrow::getEdit()
{
    if(editStart)
        return arrow_edit::START;
    if(editEnd)
        return arrow_edit::END;
    return arrow_edit::NONE;
}

void BScanArrow::setEdit(arrow_edit val)
{
    switch(val)
    {
    case (arrow_edit::START):
        editStart = true;
        break;
    case (arrow_edit::END):
        editEnd = true;
        break;
    }
}

BScanvertex *BScanArrow::findVertex(quint16 x, quint16 y)
{
    if(start->findVertex(x,y))
        return start;
    if(end->findVertex(x,y))
        return end;
    return 0;
}

void BScanArrow::resetEdit()
{
    editStart = editEnd = false;
}



