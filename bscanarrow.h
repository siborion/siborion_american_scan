#ifndef BSCANARROW_H
#define BSCANARROW_H
#include <QObject>
#include <bscanvertex.h>

enum arrow_edit{NONE, START, END};

class BScanArrow
{
private:
//    quint16 xStart, yStart, xEnd, yEnd;
    bool editStart, editEnd;

public:
    BScanArrow(quint16 , quint16 );

    BScanvertex *findVertex(quint16 x, quint16 y);
    BScanvertex *start;
    BScanvertex *end;

    quint16 getXStart();
    quint16 getYStart();
    quint16 getXEnd();
    quint16 getYEnd();
    arrow_edit  getEdit();
    void setEnd(quint16 x, quint16 y);
    void resetEdit();
    void setEdit (arrow_edit);
};

#endif // BSCANARROW_H
