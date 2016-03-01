#include "scena.h"
#include <QDebug>
#include <QMessageBox>
#include <QMenu>

scena::scena(quint16 razmer, unsigned char *p)
    :  QGLWidget()
{
    setMouseTracking(true);

    double curDeg, step;
    quint16 curX, curY, maxY, midlY, maxX, curPoint;
    QHash<quint32,quint32> map;
    quint32 key;

    buf = p;

    timer = new QTimer();
    timerRefresh = new QTimer();

    timer->setInterval(1000);
    timerRefresh->setInterval(50);

    timer->start();
    timerRefresh->start();

    start = true;

//    connect(timer, SIGNAL(timeout()), SLOT(timerSec()));
//    connect(timerRefresh, SIGNAL(timeout()), SLOT(refr()));

    step  = razmer;
    step /= 1600;

    maxY = midlY = qRound((sin(getDeg(127)))*razmer);
    maxY  *=2;
    maxX = qRound((cos(getDeg(127)))*razmer);
    setMaximumHeight(maxY);
    setMaximumWidth((double)maxY*1.3);
    setMinimumHeight(maxY);
    setMinimumWidth((double)maxY*1.3);

    for(double dVektor=(0); dVektor<=(127); dVektor+=0.1)
    {
        curPoint = qRound((double)startKonus/step);
        for(double point=curPoint*step; point<razmer; point=point+step)
        {
            curDeg = getDeg(dVektor);
            curX = qRound((cos(curDeg))*point);
            curY = qRound((sin(curDeg))*point);
            key  = curX;
            key <<= 16;
            key |= midlY+curY;
            map.insert(key, ((quint32)dVektor+127)*1600+(quint32)point);

            key = curX;
            key <<= 16;
            key |= midlY-curY;
            map.insert(key, (127-(quint32)dVektor)*1600+(quint32)point);
            curPoint++;
        }
//        qDebug()<<curPoint;
    }

    massiveSize = 0;
    QHash<quint32, quint32>::const_iterator i = map.constBegin();
    while (i != map.end())
    {
        massiv [massiveSize][0] = (i.key()>>16);
        massiv [massiveSize][1] = (i.key()&0xffff);
        massivP[massiveSize]    =  i.value();
        massiveSize++;
        ++i;
    }
    qDebug()<<"map"<<massiveSize;

    kontur[0][0]=0;
    kontur[0][1]=midlY+1;
    kontur[1][0]=maxX;
    kontur[1][1]=maxY+1;
    kontur[2][0]=0;
    kontur[2][1]=midlY;
    kontur[3][0]=maxX;
    kontur[3][1]=0;

    colorK[0][0]=0;
    colorK[0][1]=0;
    colorK[0][2]=0;
    colorK[0][3]=255;
    colorK[1][0]=0;
    colorK[1][1]=0;
    colorK[1][2]=0;
    colorK[1][3]=255;

    setAutoBufferSwap(true);
    qDebug()<< doubleBuffer() ;
}

void scena::timerSec()
{
    emit (updateFps(fps));
    fps = 0;
    if(start)
    {
        start = false;
        const char* gl_version=(const char*)(glGetString(GL_VERSION));
        QString itemText = QString::fromStdString(gl_version);
        QMessageBox msg;
        msg.setText(itemText);
        msg.exec();
    }
}

void scena::initializeGL()
{
//        QGLFormat frmt; // создать формат по умолчанию
//        frmt.setDoubleBuffer(true); // задать простую буферизацию
//        setFormat(frmt); // установить формат в контекст

    //   qglClearColor(Qt::white); // заполняем экран белым цветом
    //   glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    //   glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    //   glShadeModel(GL_SMOOTH);
    ////   glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    ////   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон

    glEnable(GL_BLEND);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


    // Сглаживание точек
//       glEnable(GL_POINT_SMOOTH);
//       glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

    // Сглаживание линий
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);

    // Сглаживание полигонов
    //   glEnable(GL_POLYGON_SMOOTH);
    //   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void scena::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //очистка буфера глубины

    for(quint32 i=0; i<massiveSize; i++)
    {
            color[i][0]=color[i][1]=color[i][2]=buf[massivP[i]];//(qrand()%255);
    }
    glVertexPointer(2, GL_SHORT,         0, massiv);
    glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
    glDrawArrays   (GL_POINTS,           0, massiveSize);

    glVertexPointer(2, GL_SHORT,         0, kontur);
    glColorPointer (4, GL_UNSIGNED_BYTE, 0, colorK);
    glDrawArrays   (GL_LINE_STRIP,       0, 2);

    glVertexPointer(2, GL_SHORT,         0, &kontur[2][0]);
    glColorPointer (4, GL_UNSIGNED_BYTE, 0, colorK);
    glDrawArrays   (GL_LINE_STRIP,       0, 2);

    QFont font;
    font.setBold(true);
    font.setPixelSize(100);

    qglColor(Qt::white); // Дальше рисуем белым цветом
//    renderText(10, 10 , 0, QString::fromUtf8("Вы набрали %1 очков:").arg(17), font , 2000);
//    renderText( 250, 250, 0, "Text" );

    drawElement();
    glLoadIdentity();
}

void scena::refr()
{
    fps++;
    this->repaint();
}

void scena::resizeGL(int nWidth, int nHeight)
{
    glOrtho(0.0, nWidth, nHeight, 0.0, -1.0, 1.0);
    glViewport(0, 0, nWidth, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //очистка буфера глубины
    glLoadIdentity(); // загрузка матрицы
}

void scena::mouseMoveEvent(QMouseEvent *mEvent)
{
    if(editVertex)
    {
        editVertex->xKoord = mEvent->x();
        editVertex->yKoord = mEvent->y();
    }
}

void scena::mousePressEvent(QMouseEvent *mEvent)
{
     QMenu menu;
    if(mEvent->button() == Qt::RightButton)
    {
        switch(editRegim)
        {
        case CUR_EDIT::NONE:

            menu.addAction("ShowMessage");
            menu.addAction("About Qt");
            menu.addSeparator();
            menu.addAction("Exit");
            menu.exec(mEvent->globalPos());
//            menu.exec();

            break;
        case CUR_EDIT::TEXT:
            break;
        case CUR_EDIT::CALIPER:
                editVertex = 0;
            break;
        case CUR_EDIT::ARROW:
            break;
        }
    }

    if(mEvent->button() == Qt::LeftButton)
    {
        switch(editRegim)
        {
        case CUR_EDIT::NONE:
            editVertex = editVertex?0:findVertex(mEvent->x(), mEvent->y());
            break;
        case CUR_EDIT::TEXT:
            break;
        case CUR_EDIT::CALIPER:
            if(editVertex)
                editVertex =  lCaliper.last()->addVertex(mEvent->x(),mEvent->y());
            else
            {
                lCaliper.append(new BScanCaliper(mEvent->x(),mEvent->y()));
                editVertex =  lCaliper.last()->addVertex(mEvent->x(),mEvent->y());
            }
            qDebug()<<"parent"<<lCaliper.last()->vertex.at(0)->parent();
            break;
        case CUR_EDIT::ARROW:
            if(editVertex)
                editVertex = 0;
            else
            {
                lArrow.append(new BScanArrow(mEvent->x(),mEvent->y()));
                editVertex =  lArrow.last()->addVertex(mEvent->x(),mEvent->y());
            }
            break;
        }
    }
}

void scena::keyPressEvent(QKeyEvent *kEvent)
{
    if(kEvent->key() == Qt::Key_Control)
    {
        ctrlPress = true;
    }
}

void scena::keyReleaseEvent(QKeyEvent *kEvent)
{
    if(kEvent->key() == Qt::Key_Control)
    {
        ctrlPress = false;
    }
}

double scena::getDeg(double val)
{
    double ret;
    ret =  Degrees;
    ret *= val;
    ret /= 2;
    ret /= 127;
    ret *= PI;
    ret /= 180;
    return ret;
}

void scena::drawElement()
{
    drawArrow();
    drawCaliper();
    if(editVertex)
        drawSelect(editVertex);
}

void scena::drawArrow()
{
    foreach(BScanArrow *arrow, lArrow)
    {
        quint8 j=0;
        foreach(BScanvertex *vx, arrow->vertex)
        {
            massiv[j][0] = vx->xKoord;
            massiv[j][1] = vx->yKoord;
            color [j][0]=color[j][1]=color[j][2]=200;
            j++;
        }
        glVertexPointer(2, GL_SHORT,         0, massiv);
        glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
        glDrawArrays   (GL_LINE_STRIP,       0, 2);
    }
}

void scena::drawCaliper()
{
    foreach(BScanCaliper *caliper, lCaliper)
    {
        quint8 j=0;
        foreach(BScanvertex *vx, caliper->vertex)
        {
            massiv[j][0] = vx->xKoord;
            massiv[j][1] = vx->yKoord;
            color [j][0]=color[j][1]=color[j][2]=200;
            j++;
        }
        massiv[j][0] = caliper->vertex.first()->xKoord;
        massiv[j][1] = caliper->vertex.first()->yKoord;
        color [j][0]=color[j][1]=color[j][2]=200;
        j++;

        glVertexPointer(2, GL_SHORT,         0, massiv);
        glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
        glDrawArrays   (GL_LINE_STRIP,       0, j);
    }
}

void scena::drawSelect(BScanvertex *vx)
{
    GLshort massivS[4][2];
    massivS[0][0] = vx->xKoord-5; massivS[0][1] = vx->yKoord-5; massivS[1][0] = vx->xKoord-5; massivS[1][1] = vx->yKoord+5; massivS[2][0] = vx->xKoord+5; massivS[2][1] = vx->yKoord+5; massivS[3][0] = vx->xKoord+5; massivS[3][1] = vx->yKoord-5;
    color[0][0]=color[0][1]=color[0][2]=color[1][0]=color[1][1]=color[1][2]=color[2][0]=color[2][1]=color[2][2]=color[3][0]=color[3][1]=color[3][2]=50;
    color[0][2]=color[1][2]=color[2][2]=color[3][2]=250;
    glVertexPointer(2, GL_SHORT,         0, massivS);
    glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
    glDrawArrays   (GL_LINE_LOOP,        0, 4);
}

BScanvertex *scena::findVertex(quint16 x, quint16 y)
{
    BScanvertex *vertex;
    foreach(BScanArrow *arrow, lArrow)
    {
        vertex = arrow->findVertex(x, y);
        if(vertex)
            return vertex;
    }
    foreach(BScanCaliper *caliper, lCaliper)
    {
        vertex = caliper->findVertex(x, y);
        if(vertex)
            return vertex;
    }
    return 0;
}

void scena::doEdit(CUR_EDIT regim, bool on)
{
    if((regim==CUR_EDIT::NONE)||(on==false))
        editRegim = CUR_EDIT::NONE;
    else
        editRegim = regim;
    qDebug()<<"editRegim"<<editRegim;
}
