#include "rasterdata.h"
#include <math.h>
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

    qDebug()<<"setData";

    for(quint16 x=0; x<=(NumPoints); x++)
    {
        for(quint16 y=0; y<=(NumVectors); y++)
        {
            mapData[x][y] = &zero;
        }
    }

    for(qint16 vektor=(-128); vektor<=(128); vektor++)
    {
        for(quint16 point=50; point<NumPoints; point++)
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
            scanData[point + (vektor+128)*1600] = 50;
        }
    }
    qDebug()<<"setData1";
}

double RasterData::value( double x, double y ) const
{
//    if((x==0)&&(y==0))
//            qDebug()<<"satrt";

//double tmp;
//tmp = scanData[(quint16)x+(quint16)y*1600];
//return (tmp);
    //    qDebug()<<"satrt";
    //    qDebug()<<"x"<<x<<"y"<<y;

    //    return 200;

    if(mapData[(quint16)x][(quint16)y]==&zero)
        return 0;
    else
    {
//        qDebug()<<"x"<<x<<"y"<<y;
        return (*mapData[(quint16)x][(quint16)y]);
    }

    //        return (*mapData[(quint16)x][(quint16)y]);
    //qDebug()<<"satrt1";
}

