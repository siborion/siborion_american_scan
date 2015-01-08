#ifndef DEVICE_H
#define DEVICE_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = 0);

private:
    QSerialPort *port;
    QTimer *timer;

signals:

private slots:
    void openDevice(bool *doMeasure);


};

#endif // DEVICE_H
