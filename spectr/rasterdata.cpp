#include "rasterdata.h"
#include <math.h>
#include <qmath.h>

const double PI = 4.*atan(1.);

RasterData::RasterData() :
    QwtRasterData()
{
    setInterval( Qt::XAxis, QwtInterval(0.0, 1600.0 ) );
    setInterval( Qt::YAxis, QwtInterval(0.0, 255.0 ) );
    setInterval( Qt::ZAxis, QwtInterval(0.0, 255.0 ) );
    for(quint16 x=0; x<NumPoints; x++)
    {
        for(quint16 y=0; y<NumVectors; y++)
        {
            mapData[x][y] = &scanData[(quint16)x+(quint16)y*1600];
        }
    }
}

void RasterData::setData(unsigned char *val)
{
    scanData = val;
    double curDeg, curX, curY;
    zero = 0;


    for(quint16 x=0; x<=(NumPoints); x++)
    {
        for(quint16 y=0; y<=(NumVectors); y++)
        {
            mapData[x][y] = &zero;
        }
    }

    for(qint16 vektor=(-128); vektor<=(128); vektor++)
    {
        for(quint16 point=50; point<=NumPoints; point++)
        {
            curDeg =  Degrees;
            curDeg /= 2;
            curDeg *= vektor;
            curDeg /= 128;
            curDeg *= PI;
            curDeg /= 180;
            curX = ((cos(curDeg))*point);
            curY = ((sin(curDeg))*point)+128;
            mapData[(quint16)curX][(quint16)curY] = &scanData[point + (vektor+128)*1600];
            scanData[point + (vektor+128)*1600] = 250;
        }
    }
    qDebug()<<"setData1";
}

double RasterData::value( double x, double y ) const
{
    double dRet=0;
    double dRetX, dRetY;
    double pX, pY;
    quint16 curX, curY;
    double dist[4];
//       if(mapData[(quint16)x][(quint16)y]==&zero)
//            return 0;
//        else
//            return (*mapData[(quint16)x][(quint16)y]);

/*
    if((x>=1)&&(x<1600)&&(y>=1)&&(y<255))
    {
        dRet  = *mapData[qRound(x)][qRound(y)];
        dRet += *mapData[qRound(x)][qRound(y+1)];
        dRet += *mapData[qRound(x+1)][qRound(y+1)];
        dRet += *mapData[qRound(x)][qRound(y-1)];
        dRet += *mapData[qRound(x-1)][qRound(y)];
        dRet /= 5;
    }
*/

    curX = qFloor(x);
    curY = qFloor(y);

    pX = x-curX;
    pY = y-curY;

/*
    dist[0] = 1-qSqrt(qPow(ostatokX,2)+qPow(ostatokY,2));
    dist[1] = 1-qSqrt(qPow(ostatokX,2)+qPow(1-ostatokY,2));
    dist[2] = 1-qSqrt(qPow(1-ostatokX,2)+qPow(1-ostatokY,2));
    dist[3] = 1-qSqrt(qPow(1-ostatokX,2)+qPow(ostatokY,2));


    return ((dist[0]>0?(*mapData[curX  ][curY  ])*dist[0]:0)+
            (dist[1]>0?(*mapData[curX  ][curY+1])*dist[1]:0)+
            (dist[2]>0?(*mapData[curX+1][curY+1])*dist[2]:0)+
            (dist[3]>0?(*mapData[curX+1][curY  ])*dist[3]:0));
*/
/*

    curX = x;
    curY = y;

    ostatokX = x-curX;
    ostatokY = y-curY;


    if((x<1599)&&(y<254))
{
    dRetX  = *mapData[curX] [curY]*(1-ostatokX);
    dRetX += *mapData[curX+1][curY]*(ostatokX);

    dRetY = *mapData[curX] [curY]*(1-ostatokY);
    dRetY += *mapData[curX][curY+1]*(ostatokX);

    dRet = dRetX+dRetY;

    dRet /=2;
}

*/




    return (dRet);

}


