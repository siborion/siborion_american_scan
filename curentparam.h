#ifndef CURENTPARAM_H
#define CURENTPARAM_H
#include <QObject>

class CurentParam //: public QObject
{
//    Q_OBJECT
private:
    static CurentParam *_instanse;

public:
    CurentParam();
    static CurentParam *instanse()
    {
        if(_instanse == NULL)
            _instanse = new CurentParam();
        return _instanse;
    }
    quint16 idPatient;
};

#endif // CURENTPARAM_H
