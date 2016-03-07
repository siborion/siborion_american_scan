#ifndef BSCAN_H
#define BSCAN_H

#include <QWidget>
#include "scena.h"
#include "bscantools.h"
#include "bscancontrol.h"
#include "BScanHard.h"

namespace Ui {
class Bscan;
}

class Bscan : public QWidget
{
    Q_OBJECT

public:
    explicit Bscan(QWidget *parent = 0);
    ~Bscan();

private:
    Ui::Bscan *ui;
    scena *pScena;
    BScanTools   *bScanTools;
    BScanControl *bScanControl;
    BScanHard     *bScanHard;
    unsigned char *buf;
    QTimer *timer;
    QTimer *timerSec;
    quint8 fps;
    bool   run;
//    findArrowEdit(quint8 nomElement, arrow_edit);

private slots:
    void scenaRefr();
    void doSec();
    void setRun();
    void doStart();
    void doStop();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // BSCAN_H
