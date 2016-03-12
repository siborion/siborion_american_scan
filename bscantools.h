#ifndef BSCANTOOLS_H
#define BSCANTOOLS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>


enum CUR_EDIT{NONE, TEXT, ARROW, ARRAY};

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


signals:
    void doScan(void);
    void doStop(void);
    void doOS(void);
    void doEdit(CUR_EDIT regim, bool on);

private slots:
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
