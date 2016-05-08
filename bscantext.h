#ifndef BSCANTEXT_H
#define BSCANTEXT_H
#include <QObject>
#include <bscanvertex.h>

//enum arrow_edit{NONE, START, END};

class BScanText: public QObject
{
     Q_OBJECT
private:

public:
    BScanText(quint16 , quint16 );
//    QList<BScanvertex*> vertex;
    QString text;
    BScanvertex *vertex;
    BScanvertex *findVertex(quint16 x, quint16 y);
    BScanvertex *addVertex(quint16 x, quint16 y);

};

#endif // BSCANARROW_H
