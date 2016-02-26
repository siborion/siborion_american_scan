#ifndef SCENA_H
#define SCENA_H
#include "QGLWidget"
#include <QTimer>
#include <math.h>
#include <qmath.h>
#include <QMouseEvent>
#include <bscanarrow.h>
#include <bscancaliper.h>
#include <bscanvertex.h>
#include <bscantools.h>

const double PI = 4.*atan(1.);
const quint8 startKonus = 30;
#define Degrees    55

class scena : public QGLWidget
{
    Q_OBJECT

public:
    scena(quint16, unsigned char*);
    void keyPressEvent  (QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    QTimer *timer;
    QTimer *timerRefresh;
    quint8 fps;
    bool start;
    quint8 bufer[256];
    float xm[1600][256];
    float ym[1600][256];
    unsigned char data[1600][256];
    GLshort massiv[400000][2];
    quint32 massivP[400000];
    GLubyte color[400000][3];
    quint16 razmer;
    quint32 massiveSize;
    double getDeg(double);
    GLshort  kontur [4][2];
    GLubyte  colorK [4][4];
    unsigned char *buf;
    QList<BScanArrow*> lArrow;
    QList<BScanCaliper*> lCaliper;
    void drawElement();
    BScanvertex *findVertex(quint16, quint16);
    bool ctrlPress;
    BScanvertex *editVertex;
    CUR_EDIT editRegim;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *mEvent);
    void initializeGL();
    void paintGL();
    void resizeGL(int nWidth, int nHeight);

public slots:
    void refr();
    void timerSec();
    void doEdit(CUR_EDIT regim, bool on);

signals:
    void updateFps(quint8);

};

#endif // SCENA_H
