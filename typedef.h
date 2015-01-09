#ifndef TYPEDEF_H
#define TYPEDEF_H

namespace Base
{
    enum TypeBase
    {
        enPatient = 0,
        enDoctor = 1,
        enLens = 2
    };
}

namespace REGIM
{
enum RegimMeasure  {AUTOFREEZ, AUTO, MANUAL};
enum RegimContact  {CONTACT,   IMMERSION};
enum RegimCataract {CATARACT,  APHAKIC};
enum RegimSide     {OD, OS};
}






#endif // TYPEDEF_H
