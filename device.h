#ifndef DEVICE_H
#define DEVICE_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QObject>
#include <qt_windows.h>
#include "ftd2xx.h"
#include "dialogserial.h"

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = 0);

private:
    QSerialPort *port;
    QTimer *timer;
    bool doDll;
    bool *doMeasure;

    FT_STATUS ftStatus;
    DWORD ftNumDevice;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    FT_HANDLE ftHandle;
    char FT_Out_Buffer[10];

    DWORD BytesWritten;
    DWORD BytesReceived;
    DWORD BytesReceivedCount;
    char RxBuffer[2048];


    QByteArray baTmp;

signals:
    void resiveData(QByteArray*);

private slots:
    void openDevice(bool *doMeasure);
    void doTimer();
    void stopMeasure();
};

#endif // DEVICE_H
