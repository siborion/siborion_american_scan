#ifndef BSCAN_H
#define BSCAN_H

#include <QWidget>
#include "scena.h"
#include "bscantools.h"
#include "bscancontrol.h"
#include "BScanHard.h"
#include <QSpacerItem>
#include "curparam.h"
#include "typedef.h"

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
    QSpacerItem *horizontalSpacer1;
    QSpacerItem *horizontalSpacer2;
    CurParam *curParam;
    REGIM::RegimSide bScanSide;
    unsigned char blackBuf[NumVectors*NumPoints];

//    findArrowEdit(quint8 nomElement, arrow_edit);

private slots:
    void scenaRefr();
    void doSec();
    void setRun(REGIM::RegimSide);
    void doStart();
    void doStop();
    void slClear();
    void slSave(QStandardItemModel*, QStandardItemModel*, QStandardItemModel*);

public slots:

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

signals:
    void sgSave(QStandardItemModel*, QStandardItemModel*, QStandardItemModel*);
};

#endif // BSCAN_H
