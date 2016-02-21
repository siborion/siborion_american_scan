#include "bscanarrow.h"

BScanArrow::BScanArrow(quint16 x, quint16 y)
{
    xStart = x;
    yStart = y;
}

void BScanArrow::setEnd(quint16 x, quint16 y)
{
    xEnd = x;
    yEnd = y;
}

quint16 BScanArrow::getXStart()
{
    return xStart;
}

quint16 BScanArrow::getYStart()
{
    return yStart;
}

quint16 BScanArrow::getXEnd()
{
    return xEnd;
}

quint16 BScanArrow::getYEnd()
{
    return yEnd;
}

arrow_edit BScanArrow::getEdit()
{
    if(editStart)
        return arrow_edit::START;
    if(editEnd)
        return arrow_edit::END;
    return arrow_edit::NONE;
}
