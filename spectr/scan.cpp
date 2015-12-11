#include "scan.h"
#include <QDebug>
#include <QtConcurrent>
#include <QMutex>

QMutex mutex;
QMutex mutexBuf1;
QMutex mutexBuf2;

Scan::Scan(QObject *parent) :
    QObject(parent)
{
    mutex.lock();
    doScan = false;
    mutex.unlock();
}

void Scan::open()
{
    qDebug()<<"true";
    mutex.lock();
    doScan = true;
    mutex.unlock();
    qDebug()<<"test"<<test;
}

void Scan::close()
{
    qDebug()<<"false";
    doScan = false;
}

void Scan::read()
{
    while(true)
    {
        mutex.lock();
        if(!doScan)
        {
            mutex.unlock();
            break;
        }
        mutex.unlock();

        mutexBuf1.lock();
        for(quint8 i=0; i<255; i++)
        {
            buf1[i]++;
        }
        mutexBuf1.unlock();

        mutexBuf2.lock();
        for(quint8 i=0; i<255; i++)
        {
            buf2[i]++;
        }
        mutexBuf2.unlock();

    }
    qDebug()<<"33";
}

void Scan::process()
{
    QFuture <void> func = QtConcurrent::run(this, &Scan::read);
    qDebug()<<"22";
}
