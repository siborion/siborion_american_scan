#ifndef BSCANARROW_H
#define BSCANARROW_H
#include <QObject>

enum arrow_edit{NONE, START, END};

class BScanArrow
{
private:
    quint16 xStart, yStart, xEnd, yEnd;
    bool editStart, editEnd;

public:
    BScanArrow(quint16 , quint16 );
    quint16 getXStart();
    quint16 getYStart();
    quint16 getXEnd();
    quint16 getYEnd();
    arrow_edit  getEdit();
    void setEnd(quint16 x, quint16 y);
};

#endif // BSCANARROW_H
