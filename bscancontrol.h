#ifndef BSCANCONTROL_H
#define BSCANCONTROL_H

#include <QWidget>
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

private slots:
    void changeRow(QModelIndex);

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
