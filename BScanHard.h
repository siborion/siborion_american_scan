#ifndef BScanHard_H
#define BScanHard_H

#include <QObject>
#include <QTimer>
#include <QMutex>
//#include <qt_windows.h>
#include "bscansize.h"

#ifdef _cplusplus
extern "C" {
#endif
#include "ftd2xx.h"
#ifdef _cplusplus
}
#endif


class BScanHard : public QObject
{
    Q_OBJECT
public:
    explicit BScanHard(QObject *parent = 0);
//    unsigned char tmpBuf[NumPoints*NumVectors];
//    unsigned char curBuf[NumPoints*NumVectors];
    unsigned char *getBuf();
    void setGain(unsigned char gain);
//    void setRun(bool start);
private:
    FT_HANDLE ftHandle;
    bool doBScanHard;
    bool first;
    quint16 test;
//    unsigned char buf1[NumPoints*NumVectors];
//    unsigned char buf2[NumPoints*NumVectors];
//    unsigned char buf3[NumPoints*NumVectors];

    unsigned char bufAll[3][80][NumPoints*NumVectors];

//    unsigned char b1[NumPoints*NumVectors];
//    unsigned char b2[NumPoints*NumVectors];
//    unsigned char b3[NumPoints*NumVectors];
    quint8 lastBuf;
    quint8 curBuf;
    quint8 curPage;
    bool   doStart, doStop;
    void sendRun(bool start);

signals:

public slots:
    void process();
    void open();
    void close();
    void read();
    void slSetSample(quint8 nomTab, quint8 nomRec, QByteArray*, quint32*);

};

#endif // BScanHard_H
