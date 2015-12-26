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
    zero1 = 128;
    zero2 = 255;


    for(quint16 x=0; x<=(NumPoints); x++)
    {
        for(quint16 y=0; y<=(NumVectors); y++)
        {
            mapData[x][y] = &zero;
        }
    }
    mapData[1][1] = &zero;
    mapData[2][1] = &zero1;
    mapData[2][2] = &zero2;

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
    double h1=1,h2=1,h3=qSin(45*PI/180)*0.5,h1d,h2d,h3d, xh3, yh3;
    double vesH1, vesH2, vesH3;
    double pX, pY;
    quint16 curX, curY;

    double dRet=0;

    if (((x>1599)||(y>255)))
        return dRet;

    curX = (x);
    curY = (y);
    pX = x-curX;
    pY = y-curY;

    xh3 = (1-pY+pX)/2;
    yh3 = 1-xh3;

    h1d = pY;
    h2d = pX;
    h3d = qSin(45*PI/180)*yh3;

    if(pX>=pY)
    {

        vesH1 = h1d;
        vesH2 = 1 - h2d;
        vesH3 = (h3-h3d)/h3;
        dRet  = (*mapData[curX+0][curY+0])*vesH2;
        dRet += (*mapData[curX+1][curY+1])*vesH1;
        dRet += (*mapData[curX+1][curY+0])*vesH3;
    }
    else
    {
//        h3d = yh3*qSin(45*PI/180);
        vesH1 = 1 - h1d;
        vesH2 = h2d;
        vesH3 = (h3d-h3)/h3;
        dRet  = (*mapData[curX+1][curY+1])*vesH2;
        dRet += (*mapData[curX+0][curY+0])*vesH1;
        dRet += (*mapData[curX+0][curY+1])*vesH3;
    }
    return (dRet);
}


