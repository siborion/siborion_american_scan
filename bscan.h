#ifndef BSCAN_H
#define BSCAN_H

#include <QWidget>
#include "scena.h"
#include "bscantools.h"
#include "bscancontrol.h"
#include "BScanHard.h"
#include "bscantabloa.h"
#include <QSpacerItem>
#include "curparam.h"

namespace Ui {
class Bscan;
}

class Bscan : public QWidget
{
    Q_OBJECT

public:
    explicit Bscan(QWidget *parent = 0, CurParam *link=0);
    ~Bscan();
    void updatePatient();

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
    BScanTabloA *bScanTabloA;
    QSpacerItem *horizontalSpacer1;
    QSpacerItem *horizontalSpacer2;
    CurParam *curParam;

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
