#ifndef RASTERDATA_H
#define RASTERDATA_H
#include <qwt_raster_data.h>
#include <qwt_color_map.h>
#include "size.h"

class RasterData: public QwtRasterData
{

public:
    explicit RasterData();
    unsigned char *scanData;
    unsigned char *mapData[1601][1601];
    void setData(unsigned char *val);
    virtual double value( double x, double y ) const;
    unsigned char zero;
    unsigned char zero1;
    unsigned char zero2;
    unsigned char one;
};

class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
//        QwtLinearColorMap( Qt::darkCyan, Qt::red )
        QwtLinearColorMap( Qt::black, Qt::white )
    {
//        addColorStop( 0.3, Qt::cyan );
//        addColorStop( 0.6, Qt::green );
//        addColorStop( 0.9, Qt::yellow );
    }
};

#endif // RASTERDATA_H
