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
    void start();
    void clearDraw();
    void setMassive(unsigned char* );

private:
    unsigned char *massive[3][80][NumPoints*NumVectors];
    Ui::BScanControl *ui;
    adjview *table;
    adjview *table0, *table1, *table2;
//    QTableView *table;
    QPushButton *pbUp, *pbDown , *pbLoad, *pbSave;
    QList<BScanButton*> pbSample;
    QTabWidget *tab;
    qint8 numTab;
    CurParam *curParam;
    unsigned char *bufAll;//[3][80][NumPoints*NumVectors];

private slots:
    void changeRow(QModelIndex);
    void slPbUpClick  (void);
    void slPbDownClick(void);
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
    void sgSetSample(quint8, quint8, QByteArray*, quint32*);

};

#endif // BSCANCONTROL_H
