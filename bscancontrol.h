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
#include "curparam.h"
#include "bscansize.h"
#include <QTimer>


namespace Ui {
class BScanControl;
}

class BScanControl : public QWidget
{
    Q_OBJECT

public:
    explicit BScanControl(QWidget *parent = 0, CurParam *link=0);
    unsigned char *getBuf();
    ~BScanControl();
    quint8 start();
    void clearDraw();
    void setMassive(unsigned char* );
    quint8 getCurTable();
    void clearTable();

private:
    QTimer *timer;
//    unsigned char *massive[3][80][NumPoints*NumVectors];
    unsigned char propuskFirstBuf;
    unsigned char *massive;
    Ui::BScanControl *ui;
    adjview *table;
    adjview *table0, *table1, *table2;
//    QTableView *table;
    QPushButton *pbPlay, *pbUp, *pbDown , *pbLoad, *pbSave;
    QList<BScanButton*> pbSample;
    QTabWidget *tab;
    qint8 numTab;
    CurParam *curParam;
    unsigned char *bufAll;//[3][80][NumPoints*NumVectors];

private slots:
    void changeTab(int);
    void changeRow0(QModelIndex);
    void changeRow1(QModelIndex);
    void changeRow2(QModelIndex);
    void changeRow(QModelIndex);
    void slPbUpClick  (void);
    void slPbDownClick(void);
    void slPbPlayClick(void);
    void slSave();
    void slLoad();

public slots:
    void changeRowFirst();
    void setBuf(unsigned char *buf);
    void slSetArray  (QString*);
    void slSetArrow  (QString*);
    void slSetCaliper(QString*);
    void slSetText   (QString*);

signals:
    void sgUpdateArray  (QString*);
    void sgUpdateArrow  (QString*);
    void sgUpdateCaliper(QString*);
    void sgUpdateText   (QString*);
    void sgSave (QStandardItemModel*, QStandardItemModel*, QStandardItemModel*);
    void sgSetSample(quint8, quint8, QByteArray*);

};

#endif // BSCANCONTROL_H
