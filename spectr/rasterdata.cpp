#include "rasterdata.h"

RasterData::RasterData() :
    QwtRasterData()
{
    setInterval( Qt::XAxis, QwtInterval(0.0, 1600.0 ) );
    setInterval( Qt::YAxis, QwtInterval(0.0, 255.0 ) );
    setInterval( Qt::ZAxis, QwtInterval( 0.0, 255.0 ) );
}

void RasterData::setData(unsigned char *val)
{
    scanData = val;
}

double RasterData::value( double x, double y ) const
{
    double tmp;
    tmp = scanData[(quint16)x+(quint16)y*1600];
    return (tmp);
}

