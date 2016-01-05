#include "rasterdata.h"
#include <math.h>
#include <qmath.h>

//0x80
//0x0h
//0x0l


const double PI = 4.*atan(1.);

RasterData::RasterData() :
    QwtRasterData()
{
    setInterval( Qt::XAxis, QwtInterval(0.0, 1600.0 ) );
    setInterval( Qt::YAxis, QwtInterval(0.0, 1600.0 ) );
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
    qint16 vektor;
    scanData = val;
    double curDeg, curX, curY;
    zero = -127;
    zero1 = 128;
    zero2 = 255;

    qDebug()<<"setData0";

    for(quint16 x=0; x<=(1600); x++)
    {
        for(quint16 y=0; y<=(1600); y++)
        {
            mapData[x][y] = &zero;
        }
    }

    qDebug()<<"setData01";

    //    mapData[1][1] = &zero;
    //    mapData[2][1] = &zero1;
    //    mapData[2][2] = &zero2;

    for(double dVektor=(-128); dVektor<=(127); dVektor+=0.1)
    {
        for(quint16 point=50; point<=NumPoints; point++)
        {
            curDeg =  Degrees;
            curDeg /= 2;
            curDeg *= dVektor;
            curDeg /= 128;
            curDeg *= PI;
            curDeg /= 180;
            curX = ((cos(curDeg))*point);
            curY = ((sin(curDeg))*point)+800;

            vektor = qRound(dVektor);

            mapData[qRound(curX)][qRound(curY)] = &scanData[point + (vektor+128)*1600];
            scanData[point + (vektor+128)*1600] = 128;//qAbs(vektor);

//            if(((vektor==0)&&(point==1590))||((vektor==120)&&(point==1590)))
            {
//                mapData[qRound(curX)][qRound(curY)+1] = &scanData[point + (vektor+128)*1600];
//                mapData[qRound(curX)][qRound(curY)+2] = &scanData[point + (vektor+128)*1600];
//                mapData[qRound(curX)][qRound(curY)+3] = &scanData[point + (vektor+128)*1600];
//                mapData[qRound(curX)][qRound(curY)-1] = &scanData[point + (vektor+128)*1600];
//                mapData[qRound(curX)][qRound(curY)-2] = &scanData[point + (vektor+128)*1600];
//                mapData[qRound(curX)][qRound(curY)-3] = &scanData[point + (vektor+128)*1600];
                scanData[point + (vektor+128)*1600] = qAbs(vektor);
            }
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

    double dRet=128;


    curX = (x);
    curY = (y);

    if (((curX>1599)||(curY>1599)))
        return dRet;

    if((qAbs(curY-800)*1.9)>(curX))
         return dRet;

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
        vesH1 = 1 - h1d;
        vesH2 = h2d;
        vesH3 = (h3d-h3)/h3;
        dRet  = (*mapData[curX+1][curY+1])*vesH2;
        dRet += (*mapData[curX+0][curY+0])*vesH1;
        dRet += (*mapData[curX+0][curY+1])*vesH3;
    }
    return (dRet);
}


