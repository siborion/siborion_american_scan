#ifndef BSCANTOOLS_H
#define BSCANTOOLS_H

#include <QWidget>

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

signals:
    void doScan(void);
    void doStop(void);
    void doOS(void);

private slots:
    void on_pbScan_clicked();
    void on_pbStop_clicked();
    void on_pbOS_clicked();

};

#endif // BSCANTOOLS_H
