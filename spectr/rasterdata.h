#ifndef RASTERDATA_H
#define RASTERDATA_H
#include <qwt_raster_data.h>
#include <qwt_color_map.h>

class RasterData: public QwtRasterData
{
public:
    unsigned char *scanData;

    RasterData()
    {
        setInterval( Qt::XAxis, QwtInterval(0.0, 1600.0 ) );
        setInterval( Qt::YAxis, QwtInterval(0.0, 255.0 ) );
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 255.0 ) );
    }

    void setData(unsigned char *val)
    {
        scanData = val;
    }

    virtual double value( double x, double y ) const
    {
        double tmp;
        tmp = scanData[(quint16)x+(quint16)y*1600];
        return (tmp);
    }
};

class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::darkCyan, Qt::red )
    {
        addColorStop( 0.3, Qt::cyan );
        addColorStop( 0.6, Qt::green );
        addColorStop( 0.9, Qt::yellow );
    }
};

#endif // RASTERDATA_H
