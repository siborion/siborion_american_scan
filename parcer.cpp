#include "parcer.h"
#include <QDebug>

Parcer::Parcer(QObject *parent, CurParam *link) :
    QObject(parent)
{
    curParam = link;
//    qDebug()<<link;
//    link->regimCataract = REGIM::CATARACT;
//    curParam->regimCataract = REGIM::CATARACT;

    //RegimCataract::APHAKIC;//   RegimMeasure::AUTOFREEZ;
}

bool Parcer::findExtremum(QByteArray *Sample, QList<quint16> *extremum)
{
    bool corneaEn, lens1En, lens2En, retinaEn;
    corneaEn = lens1En = lens2En = retinaEn = false;
    qint16 tmp;

    extremum->clear();
    curParam->Start = curParam->L1 = curParam->L2 = curParam->Retina = 0;

    parseCornea =  new  parserFront(curParam->corneaX1, curParam->corneaX2, 7, 0,  0);
    parseLens   =  new  parserFront(curParam->lensX1,   curParam->lensX2,   7, 27, 30);
    parseRetina =  new  parserFront(curParam->retinaX1, curParam->retinaX2, 7, 54, 0);

    for(int i=0; i<Sample->count(); i++)
    {
        tmp=parseCornea->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!corneaEn)
                curParam->Start = tmp;
            corneaEn = true;
            extremum->append(tmp);
        }

        tmp=parseLens->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!lens1En)
            {
                curParam->L1 = tmp;
                lens1En = true;
            }
            else
            {
                if(!lens2En)
                {
                    curParam->L2 = tmp;
                    lens2En = true;
                }
            }
            extremum->append(tmp);
        }

        tmp=parseRetina->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!retinaEn)
                curParam->Retina = tmp;
            retinaEn = true;
            extremum->append(tmp);
        }
    }

//    allExtremum = extremum;

    if((curParam->regimCataract == REGIM::APHAKIC)||(curParam->regimMeasure == REGIM::MANUAL))
        return (corneaEn && retinaEn);
    else
        return (corneaEn && lens1En && lens2En && retinaEn);
}
