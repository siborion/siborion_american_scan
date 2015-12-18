#ifndef RASTERDATA_H
#define RASTERDATA_H
#include <qwt_raster_data.h>
#include <qwt_color_map.h>

class RasterData: public QwtRasterData
{

public:
    explicit RasterData();
    unsigned char *scanData;
    void setData(unsigned char *val);
    virtual double value( double x, double y ) const;
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
