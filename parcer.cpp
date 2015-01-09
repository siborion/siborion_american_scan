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

bool Parcer::findExtremum(QByteArray *Sample, QList<quint16> &extremum)
{
    bool corneaEn, lens1En, lens2En, retinaEn;
    corneaEn = lens1En = lens2En = retinaEn = false;
    qint16 tmp;

    extremum.clear();
    curParam->Start = curParam->L1 = curParam->L2 = curParam->Retina = 0;

//    parseCornea =  new  parserFront(curentParam->corneaX1, curentParam->corneaX2, 7, 0,  0);
//    parseLens   =  new  parserFront(curentParam->lensX1,   curentParam->lensX2,   7, 27, 30);
//    parseRetina =  new  parserFront(curentParam->retinaX1, curentParam->retinaX2, 7, 54, 0);

//    for(int i=0; i<Sample->count(); i++)
//    {
//        tmp=parseCornea->parser(i,Sample->at(i));
//        if(tmp>=0)
//        {
//            if(!corneaEn)
//                mainParam.Start = tmp;
//            corneaEn = true;
//            extremum.append(tmp);
//        }

//        tmp=parseLens->parser(i,Sample->at(i));
//        if(tmp>=0)
//        {
//            if(!lens1En)
//            {
//                mainParam.L1 = tmp;
//                lens1En = true;
//            }
//            else
//            {
//                if(!lens2En)
//                {
//                    mainParam.L2 = tmp;
//                    lens2En = true;
//                }
//            }
//            extremum.append(tmp);
//        }

//        tmp=parseRetina->parser(i,Sample->at(i));
//        if(tmp>=0)
//        {
//            if(!retinaEn)
//                mainParam.Retina = tmp;
//            retinaEn = true;
//            extremum.append(tmp);
//        }
//    }

//    allExtremum = extremum;

//    if((curentParam->regimCataract == RegimCataract::APHAKIC)||(curentParam->regimMeasure == RegimMeasure::MANUAL))
//        return (corneaEn && retinaEn);
//    else
//        return (corneaEn && lens1En && lens2En && retinaEn);
}
