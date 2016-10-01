#ifndef BSCANTOOLS_H
#define BSCANTOOLS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <scanbutton.h>
#include "typedef.h"


enum CUR_EDIT{NONE, TEXT, ARROW, ARRAY, CALIPER};

namespace Ui {
class BScanTools;
}

class BScanTools : public QWidget
{
    Q_OBJECT

public:
    explicit BScanTools(QWidget *parent = 0);
    ~BScanTools();
    void setFps(quint8);

private:
    Ui::BScanTools *ui;
    void rechecketPb(QGroupBox*, QPushButton *pb);
    ScanButton *scanButton;
    bool *linkScan;

signals:
    void doScan(void);
    void doStop(void);
    void doOS(REGIM::RegimSide);
    void doEdit(CUR_EDIT regim, bool on);
    void doClear();

private slots:
    void slDoScan(bool*);
    void slDoStop();
    void on_pbScan_clicked();
    void on_pbStop_clicked();
    void on_pbOS_clicked();

    void on_pbClear_clicked();
    void on_pbText_clicked();
    void on_pbCaliper_clicked();
    void on_pbArray_clicked();
    void on_pbArrow_clicked();
};

#endif // BSCANTOOLS_H
