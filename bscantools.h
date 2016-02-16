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

private:
    Ui::BScanTools *ui;

signals:
    void doScan(void);

private slots:
    void on_pbScan_clicked();
};

#endif // BSCANTOOLS_H
