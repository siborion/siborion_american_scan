#ifndef BSCANVERTEX_H
#define BSCANVERTEX_H
#include <QObject>

class BScanvertex : public QObject
{
     Q_OBJECT

public:
    BScanvertex(QObject *parent = 0, quint16 x=0, quint16 y=0);
    quint16 xKoord, yKoord;
    BScanvertex *findVertex(quint16 x, quint16 y);
    bool vertexEdit();
private:
    bool edit;
};

#endif // BSCANVERTEX_H
