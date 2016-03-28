#include "scena.h"
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QApplication>

scena::scena(quint16 raz, unsigned char *p)
    :  QGLWidget()
{
    setMouseTracking(true);
    razmer = raz;
    newObject = false;

    double curDeg, step;
    quint16 curX, curY, maxY, maxX, curPoint;
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

    step  = 1600;
    step /= razmer;

    maxY  = midlY = qRound((sin(getDeg(127)))*razmer);
    maxY *=2;
    maxX  = qRound((cos(getDeg(127)))*razmer);
    setMaximumHeight(maxY);
    setMaximumWidth((double)maxY*1.3);
    setMinimumHeight(maxY);
    setMinimumWidth((double)maxY*1.3);

    for(double dVektor=(0); dVektor<=(127); dVektor+=0.1)
    {
        curPoint = qRound((double)startKonus/step);
        for(double point=curPoint*step; point<1600; point=point+step)
        {
            curDeg = getDeg(dVektor);
            curX = qRound((cos(curDeg))*curPoint);
            curY = qRound((sin(curDeg))*curPoint);
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
    curRazrez = midlY;
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

//    qDebug()<<"buf"<<buf;

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

void scena::refr(unsigned char *p)
{
    buf = p;
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
    double x;
    Qt::MouseButtons buttons = QApplication::mouseButtons();
    if((editVertex)&&(buttons.testFlag(Qt::LeftButton)||newObject))
    {
        if(lArrow.at(0)->vertex.at(1) == editVertex)
        {
            editVertex->yKoord = curRazrez = mEvent->y();
//            editVertex->xKoord = 200;
//            editVertex->xKoord = qRound(cos(getDeg(abs(curRazrez-midlY)))*razmer);
            x =  (cos(getDeg(abs(curRazrez-midlY))));
            qDebug()<<"xKoord"<<x;
            x *= razmer;
            qDebug()<<"xKoord"<<razmer;
            editVertex->xKoord = qRound(x);
//            qDebug()<<"xKoord"<<(cos(getDeg(abs(curRazrez-midlY))))*razmer;

//            curDeg = getDeg(dVektor);
//            curX = qRound((cos(curDeg))*curPoint);



        }
        else
        {
            editVertex->xKoord = mEvent->x();
            editVertex->yKoord = mEvent->y();
        }
    }
}

void scena::mousePressEvent(QMouseEvent *mEvent)
{
    QMenu menu;
    BScanvertex   *tmpVertex;

    tmpVertex = findVertex(mEvent->x(), mEvent->y());

    if(mEvent->button() == Qt::RightButton)
    {
        if(newObject)
        {
            removeEditVertex();
            newObject = false;
        }
        else
        {
            editVertex = findVertex(mEvent->x(), mEvent->y());
            if(editVertex)
            {
                editArrow    = dynamic_cast<BScanArrow   *>(editVertex->parent());
                editArray    = dynamic_cast<BScanArray   *>(editVertex->parent());
                editCaliper  = dynamic_cast<BScanCaliper *>(editVertex->parent());
                if(editArray==0)
                    menu.addAction("Delete vertex",this,SLOT(removeEditVertex()));
                menu.addAction("Delete object",this,SLOT(removeEditObject()));
                menu.exec(mEvent->globalPos());
            }
        }
    }

    if(mEvent->button() == Qt::LeftButton)
    {
        switch(editRegim)
        {
        case CUR_EDIT::NONE:
            editVertex = tmpVertex;
            break;
        case CUR_EDIT::TEXT:
            break;
        case CUR_EDIT::ARRAY:
            if(editVertex&&newObject)
                editVertex =  lArray.last()->addVertex(mEvent->x(),mEvent->y());
            else
            {
                if(tmpVertex)
                    editVertex = tmpVertex;
                else
                {
                    newObject = true;
                    lArray.append(new BScanArray(mEvent->x(),mEvent->y()));
                    editVertex =  lArray.last()->addVertex(mEvent->x(),mEvent->y());
                }
            }
            break;
        case CUR_EDIT::ARROW:
            if(editVertex&&newObject)
            {
                editVertex = 0;
                newObject = false;
            }
            else
            {
                if(tmpVertex)
                    editVertex = tmpVertex;
                else
                {
                    newObject = true;
                    lArrow.append(new BScanArrow(mEvent->x(),mEvent->y()));
                    editVertex =  lArrow.last()->addVertex(mEvent->x(),mEvent->y());
                }
            }
            break;
        case CUR_EDIT::CALIPER:
            if(editVertex&&newObject)
            {
                editVertex = 0;
                newObject = false;
            }
            else
            {
                if(tmpVertex)
                    editVertex = tmpVertex;
                else
                {
                    newObject = true;
                    lCaliper.append(new BScanCaliper(mEvent->x(),mEvent->y()));
                    editVertex =  lCaliper.last()->addVertex(mEvent->x(),mEvent->y());
                }
            }
            break;
        }
    }
    if(editVertex)
    {
        editArrow    = dynamic_cast<BScanArrow   *>(editVertex->parent());
        editArray    = dynamic_cast<BScanArray   *>(editVertex->parent());
        editCaliper  = dynamic_cast<BScanCaliper *>(editVertex->parent());
    }
    else
    {
        editArrow = 0;
        editArray = 0;
        editCaliper = 0;
    }

    if((mEvent->button() == Qt::RightButton)||(mEvent->button() == Qt::LeftButton))
    {
        QString sTmp;
        sTmp.append(getArrowString());
        emit sgUpdateArrow(&sTmp);
        sTmp.clear();
        sTmp.append(getArrayString());
        emit sgUpdateArray(&sTmp);
        sTmp.clear();
        sTmp.append(getCaliperString());
        emit sgUpdateCaliper(&sTmp);
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
    drawArray();
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
            if(vx==arrow->vertex.last())
                drawCrest(massiv[j][0],massiv[j][1]);
            color [j][0]=color[j][1]=color[j][2]=0;
            color[j][1]=255;
            if(editArrow==arrow)
            {
                color[j][1]=0;
                color[j][2]=255;
            }
            j++;
        }
        glVertexPointer(2, GL_SHORT,         0, massiv);
        glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
        glDrawArrays   (GL_LINE_STRIP,       0, 2);
    }
}

void scena::drawArray()
{
    foreach(BScanArray *array, lArray)
    {
        quint8 j=0;
        foreach(BScanvertex *vx, array->vertex)
        {
            massiv[j][0] = vx->xKoord;
            massiv[j][1] = vx->yKoord;
            color [j][0]=color[j][2]=0;
            color[j][1]=255;
            if(editArray==array)
            {
                color[j][1]=0;
                color[j][2]=255;
            }
            j++;
        }
        massiv[j][0] = array->vertex.first()->xKoord;
        massiv[j][1] = array->vertex.first()->yKoord;
        color [j][0]=color[j][2]=150;
        color[j][1]=255;
        if(editArray==array)
        {
            color[j][1]=0;
            color[j][2]=255;
        }
        j++;

        glVertexPointer(2, GL_SHORT,         0, massiv);
        glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
        glDrawArrays   (GL_LINE_STRIP,       0, j);
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
            drawCrest(massiv[j][0],massiv[j][1]);
            color [j][0]=color[j][1]=color[j][2]=0;
            color[j][1]=255;
            if(editCaliper==caliper)
            {
                color[j][1]=0;
                color[j][2]=255;
            }
            j++;
        }
        glVertexPointer(2, GL_SHORT,         0, massiv);
        glColorPointer (3, GL_UNSIGNED_BYTE, 0, color);
        glDrawArrays   (GL_LINE_STRIP,       0, 2);
    }
}

void scena::drawCrest(quint16 x, quint16 y)
{
    GLshort crest[2][2];
    GLubyte crestColor[2][3];
    crest[0][0] = x-5;
    crest[0][1] = y-5;
    crest[1][0] = x+5;
    crest[1][1] = y+5;
    crestColor [0][0]=crestColor[0][1]=crestColor[0][2]=150;
    crestColor [1][0]=crestColor[1][1]=crestColor[1][2]=150;
    glVertexPointer(2, GL_SHORT,         0, crest);
    glColorPointer (3, GL_UNSIGNED_BYTE, 0, crestColor);
    glDrawArrays   (GL_LINE_STRIP,       0, 2);
    crest[0][0] = x-5;
    crest[0][1] = y+5;
    crest[1][0] = x+5;
    crest[1][1] = y-5;
    glVertexPointer(2, GL_SHORT,         0, crest);
    glColorPointer (3, GL_UNSIGNED_BYTE, 0, crestColor);
    glDrawArrays   (GL_LINE_STRIP,       0, 2);
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
    foreach(BScanArray *array, lArray)
    {
        vertex = array->findVertex(x, y);
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
}

void scena::removeEditVertex()
{
    if(editArrow)
    {
        editArrow->vertex.removeOne(editVertex);
        editArrow = 0;
        editVertex = 0;
    }
    if(editArray)
    {
        editArray->vertex.removeOne(editVertex);
        editVertex = 0;
    }
    if(editCaliper)
    {
        editCaliper->vertex.removeOne(editVertex);
        editVertex = 0;
    }
}

void scena::removeEditObject()
{
    if(editArrow)
    {
        lArrow.removeOne(editArrow);
        editArrow = 0;
        editVertex = 0;
    }
    if(editArray)
    {
        lArray.removeOne(editArray);
        editArray = 0;
        editVertex = 0;
    }
    if(editCaliper)
    {
        lCaliper.removeOne(editCaliper);
        editArray = 0;
        editVertex = 0;
    }
}


QString  scena::getArrowString()
{
    QString sTmp;
    bool newArrow;
    foreach(BScanArrow *arrow, lArrow)
    {
        newArrow = true;
        foreach(BScanvertex *vx, arrow->vertex)
        {
            if(!newArrow)
                sTmp.append(";");
            sTmp.append(QString("%1,%2").arg(vx->xKoord).arg(vx->yKoord));
            newArrow = false;
        }
        sTmp.append("|");
    }
    return sTmp;
}

QString  scena::getArrayString()
{
    QString sTmp;
    bool newArray;
    foreach(BScanArray *array, lArray)
    {
        newArray = true;
        foreach(BScanvertex *vx, array->vertex)
        {
            if(!newArray)
                sTmp.append(";");
            sTmp.append(QString("%1,%2").arg(vx->xKoord).arg(vx->yKoord));
            newArray = false;
        }

        sTmp.append("|");
    }
    return sTmp;
}

QString  scena::getCaliperString()
{
    QString sTmp;
    bool newCaliper;
    foreach(BScanCaliper *caliper, lCaliper)
    {
        newCaliper = true;
        foreach(BScanvertex *vx, caliper->vertex)
        {
            if(!newCaliper)
                sTmp.append(";");
            sTmp.append(QString("%1,%2").arg(vx->xKoord).arg(vx->yKoord));
            newCaliper = false;
        }
        sTmp.append("|");
    }
    return sTmp;
}


void     scena::setArrow  (QString *str)
{
    quint8   i = 0;
    quint16  coord[2];
//    bool newArrow = false;
    QStringList slArrow = str->split("|");
    lArrow.clear();
    lArrow.append(new BScanArrow(0, midlY));
    lArrow.last()->addVertex(200,   curRazrez);
    foreach(QString sArrow, slArrow)
    {
//        newArrow = true;

        QStringList slVertex = sArrow.split(";");
        foreach(QString sVertex, slVertex)
        {
            QStringList slVertex = sVertex.split(",");
            foreach(QString sPoint, slVertex)
            {
                coord[i++] = sPoint.toUInt();
                if(i==2)
                {
                    lArrow.last()->addVertex(coord[0],coord[1]);
                    i=0;
                }
            }
        }
    }
}

void     scena::setArray  (QString *str)
{
    quint8   i = 0;
    quint16  coord[2];
    bool newArray = false;
    QStringList slArray = str->split("|");
    lArray.clear();
    foreach(QString sArray, slArray)
    {
        newArray = true;
        QStringList slVertex = sArray.split(";");
        foreach(QString sVertex, slVertex)
        {
            QStringList slVertex = sVertex.split(",");
            foreach(QString sPoint, slVertex)
            {
                coord[i++] = sPoint.toUInt();
                if(i==2)
                {
                    if(newArray)
                        lArray.append(new BScanArray(coord[0],coord[1]));
                    else
                        lArray.last()->addVertex(coord[0],coord[1]);
                    newArray = false;
                    i=0;
                }
            }
        }
    }
}

void     scena::setCaliper(QString *str)
{
    quint8   i = 0;
    quint16  coord[2];
    bool newCaliper = false;
    QStringList slCaliper = str->split("|");
    lCaliper.clear();
    foreach(QString sCaliper, slCaliper)
    {
        newCaliper = true;
        QStringList slVertex = sCaliper.split(";");
        foreach(QString sVertex, slVertex)
        {
            QStringList slVertex = sVertex.split(",");
            foreach(QString sPoint, slVertex)
            {
                coord[i++] = sPoint.toUInt();
                if(i==2)
                {
                    if(newCaliper)
                        lCaliper.append(new BScanCaliper(coord[0],coord[1]));
                    else
                        lCaliper.last()->addVertex(coord[0],coord[1]);
                    newCaliper = false;
                    i=0;
                }
            }
        }
    }
}





