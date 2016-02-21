#ifndef BSCANVERTEX_H
#define BSCANVERTEX_H
#include <QObject>

class BScanvertex
{
public:
    BScanvertex(quint16 x, quint16 y);
    quint16 xKoord, yKoord;
    BScanvertex *findVertex(quint16 x, quint16 y);
    bool vertexEdit();
private:
    bool edit;
};

#endif // BSCANVERTEX_H
