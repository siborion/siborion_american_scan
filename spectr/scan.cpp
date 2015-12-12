#include "scan.h"
#include <QDebug>
#include <QtConcurrent>
#include <QMutex>

QMutex mutex;
QMutex mutexBuf1;
QMutex mutexBuf2;
QMutex mutexBuf3;

Scan::Scan(QObject *parent) :
    QObject(parent)
{
    //    mutex.lock();
    //    doScan = false;
    //    mutex.unlock();
}

void Scan::open()
{
    //    qDebug()<<"true";
    //    mutex.lock();
    //    doScan = true;
    //    mutex.unlock();
    //    qDebug()<<"test"<<test;
}

unsigned char *Scan::getBuf()
{
    switch(lastBuf)
    {
    case 1:
        if(mutexBuf1.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf1[i];
            }
        mutexBuf1.unlock();
        }
        break;
    case 2:
        if(mutexBuf2.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf2[i];
            }
        mutexBuf2.unlock();
        }
        break;
    case 3:
        if(mutexBuf3.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                curBuf[i]=buf3[i];
            }
        mutexBuf3.unlock();
        }
        break;
    }
    return curBuf;
}

void Scan::close()
{
    mutex.lock();
    qDebug()<<"false";
    doScan = false;
    mutex.unlock();
}

void Scan::read()
{
    qDebug()<<"00";
    while(true)
    {
        if(mutex.tryLock())
        {
            if(!doScan)
            {
                mutex.unlock();
                qDebug()<<"return";
                break;
            }
            mutex.unlock();
        }

        if(mutexBuf1.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                buf1[i]=qrand();
            }
            mutexBuf1.unlock();
            lastBuf = 1;
        }

        if(mutexBuf2.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                buf2[i]=qrand();
            }
            mutexBuf2.unlock();
            lastBuf = 2;
        }

        if(mutexBuf3.tryLock())
        {
            for(quint32 i=0; i<NumVectors*NumPoints-1; i++)
            {
                buf3[i]=qrand();
            }
            mutexBuf3.unlock();
            lastBuf = 3;
        }
    }
    qDebug()<<"33";
}

void Scan::process()
{
    doScan = true;
    QFuture <void> func = QtConcurrent::run(this, &Scan::read);
    qDebug()<<"22";
}
