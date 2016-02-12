#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_raster_data.h>
#include "rasterdata.h"

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    explicit Plot( QWidget * = NULL, unsigned char *val = 0 );

    QSize sizeHint() const
    {
        return QSize(10, heightForWidth(10));
    }
    int heightForWidth(int w) const
    {
        return w / 1;
    }

public Q_SLOTS:
    void showContour( bool on );
    void showSpectrogram( bool on );
    void setAlpha( int );
    void updateScan();
//    quint8 dataScan[1024];

#ifndef QT_NO_PRINTER
    void printPlot();
#endif

private:
    QwtPlotSpectrogram *d_spectrogram;
    unsigned char *dataScan;
    RasterData *spectrogramData;

};
