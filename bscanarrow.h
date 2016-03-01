#ifndef BSCANARROW_H
#define BSCANARROW_H
#include <QObject>
#include <bscanvertex.h>

//enum arrow_edit{NONE, START, END};

class BScanArrow: public QObject
{
     Q_OBJECT
private:

public:
    BScanArrow(quint16 , quint16 );
    QList<BScanvertex*> vertex;
    BScanvertex *findVertex(quint16 x, quint16 y);
    BScanvertex *addVertex(quint16 x, quint16 y);
};

#endif // BSCANARROW_H
