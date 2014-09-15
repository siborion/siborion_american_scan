#ifndef SCANBUTTON_H
#define SCANBUTTON_H
#include <QPushButton>
#include <QTimer>

class ScanButton : public QPushButton
{
    Q_OBJECT

public:
    ScanButton();

private:
    QTimer *timer;
    quint8 numPic;

private slots:
    void doTimer();

};

#endif // SCANBUTTON_H
