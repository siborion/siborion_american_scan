#ifndef SCAN_H
#define SCAN_H

#include <QObject>
#include <qt_windows.h>
#define NumVectors 256
#define NumPoints  1600

#ifdef _cplusplus
extern "C" {
#endif
#include "ftd2xx.h"
#ifdef _cplusplus
}
#endif


class Scan : public QObject
{
    Q_OBJECT
public:
    explicit Scan(QObject *parent = 0);
    unsigned char curBuf[NumPoints*NumVectors];
    unsigned char *getBuf();

private:
    FT_HANDLE ftHandle;
    bool doScan;
    bool first;
    quint16 test;
    unsigned char buf1[NumPoints*NumVectors];
    unsigned char buf2[NumPoints*NumVectors];
    unsigned char buf3[NumPoints*NumVectors];
    quint8 lastBuf;


signals:

public slots:
    void process();
    void open();
    void close();
    void read();

};

#endif // SCAN_H
