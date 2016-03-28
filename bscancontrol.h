#ifndef BSCANCONTROL_H
#define BSCANCONTROL_H

#include <QWidget>
#include <QPushButton>
#include "adjview.h"
#include "bscanarray.h"
#include "bscanarrow.h"
#include "bscancaliper.h"

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

private:
    Ui::BScanControl *ui;
    adjview *table;
    QPushButton *pbUp, *pbDown;

private slots:
    void changeRow(QModelIndex);
    void slPbUpClick  (void);
    void slPbDownClick(void);

public slots:
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
