#ifndef SCANBUTTON_H
#define SCANBUTTON_H
#include <QPushButton>
#include <QTimer>

class ScanButton : public QPushButton
{
    Q_OBJECT

public:
    ScanButton();
    bool doMeasure;

private:
    QTimer *timer;
    quint8 numPic;

private slots:
    void doTimer();
    void doScanSlot();

Q_SIGNALS:
    void doScan(bool*);


};

#endif // SCANBUTTON_H
