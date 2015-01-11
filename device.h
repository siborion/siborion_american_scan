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
    bool doDll;
    bool *doMeasure;

signals:
    void resiveData(QByteArray);

private slots:
    void openDevice(bool *doMeasure);
    void doTimer();
    void stopMeasure();


};

#endif // DEVICE_H
