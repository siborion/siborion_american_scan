#ifndef BSCANCONTROL_H
#define BSCANCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include "adjview.h"
#include "bscanarray.h"
#include "bscanarrow.h"
#include "bscancaliper.h"
#include "bscanbutton.h"

namespace Ui {
class BScanControl;
}

class BScanControl : public QWidget
{
    Q_OBJECT

public:
    explicit BScanControl(QWidget *parent = 0);
    unsigned char *getBuf();
    ~BScanControl();
    void start();
    void clearDraw();

private:
    Ui::BScanControl *ui;
    adjview *table;
    adjview *table0, *table1, *table2;
//    QTableView *table;
    QPushButton *pbUp, *pbDown , *pbLoad, *pbSave;
    QList<BScanButton*> pbSample;
    QTabWidget *tab;
    qint8 numTab;

private slots:
    void changeRow(QModelIndex);
    void slPbUpClick  (void);
    void slPbDownClick(void);

public slots:
    void changeRowFirst();
    void setBuf(unsigned char *buf);
    void slSetArray  (QString*);
    void slSetArrow  (QString*);
    void slSetCaliper(QString*);

signals:
    void sgUpdateArray  (QString*);
    void sgUpdateArrow  (QString*);
    void sgUpdateCaliper(QString*);

};

#endif // BSCANCONTROL_H
