#ifndef BSCAN_H
#define BSCAN_H

#include <QWidget>
#include "d:/_SVN/SibOrion/OpenGl/Opengl/scena.h"
#include "bscantools.h"
#include "bscancontrol.h"
#include "bscanusb.h"
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

};

#endif // BSCAN_H
