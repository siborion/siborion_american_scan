#ifndef SCAN_H
#define SCAN_H

#include <QObject>
#include <qt_windows.h>

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
    unsigned char buf1[255];
    unsigned char buf2[255];

private:
    FT_HANDLE ftHandle;
    bool doScan;
    bool first;
    quint16 test;
signals:

public slots:
    void process();
    void open();
    void close();
    void read();

};

#endif // SCAN_H
