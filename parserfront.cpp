#include "parserfront.h"

parserFront::parserFront(quint16 start, quint16 end, quint8 front, quint8 zero, quint8 max)
{
    intervalStart = start;
    intervalEnd = end;
    lenthFront = front;
    lenhtZero = zero;
    maxZero = max;
    countFront = countZero = 0;
    extremum = false;
}

qint16 parserFront::parser(quint16 pos, quint8 val)
{
    if(val<=maxZero)
    {
        level60 = 0;
        countFront = 0;
        countZero++;
        extremum = false;
    }
    else
    {
        if((val>=60)&&(level60==0))
            level60 = pos;

        countFront++;

        if(val>=230)
        {
            if((countFront<=lenthFront)&&(countZero>=lenhtZero))
            {
                if((pos>=intervalStart)&&(pos<=intervalEnd))
                {
                    if(!extremum)
                    {
                        extremum = true;
                        return (level60);
                    }
                }
            }
            countZero=0;
        }
    }
    return (-1);
}
