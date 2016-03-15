#ifndef SCENA_H
#define SCENA_H
#include "QGLWidget"
#include <QTimer>
#include <math.h>
#include <qmath.h>
#include <QMouseEvent>
#include <bscanarrow.h>
#include <bscanarray.h>
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

    QString  getArrowString();
    QString  getArrayString();
    QString  getCaliperString();

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
    QList<BScanArrow*>   lArrow;
    QList<BScanArray*>   lArray;
    QList<BScanCaliper*> lCaliper;
    void drawElement();
    void drawArrow();
    void drawArray();
    void drawCaliper();
    void drawCrest(quint16, quint16);
    void drawSelect(BScanvertex *vx);
    BScanvertex *findVertex(quint16, quint16);
    bool ctrlPress;
    BScanvertex   *editVertex;
    CUR_EDIT       editRegim;
    BScanArrow    *editArrow;
    BScanArray    *editArray;
    BScanCaliper  *editCaliper;
    bool          newObject;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *mEvent);
    void initializeGL();
    void paintGL();
    void resizeGL(int nWidth, int nHeight);

private slots:
    void removeEditVertex();
    void removeEditObject();

public slots:
    void refr(unsigned char *);
    void timerSec();
    void doEdit(CUR_EDIT regim, bool on);
    void     setArrow  (QString*);
    void     setArray  (QString*);
    void     setCaliper(QString*);

signals:
    void updateFps(quint8);
    void sgUpdateArrow  (QString*);
    void sgUpdateArray  (QString*);
    void sgUpdateCaliper(QString*);

};

QDataStream &operator <<(QDataStream &out, QList<BScanCaliper*> &any);

#endif // SCENA_H
