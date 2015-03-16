#include "parcer.h"
#include <QDebug>
#include <math.h>

Parcer::Parcer(QObject *parent, CurParam *link) :
    QObject(parent)
{
    curParam = link;
}

bool Parcer::findExtremum(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam *measureParam)
{
    bool bValid = false;
    bool corneaEn, lens1En, lens2En, retinaEn;
    corneaEn = lens1En = lens2En = retinaEn = false;
    qint16 tmp;

    extremum->clear();
    measureParam->Cornea = measureParam->L1 = measureParam->L2 = measureParam->Retina = 0;

    parseCornea =  new  parserFront(curParam->corneaX1, curParam->corneaX2, 7, 0,  0);
    parseLens   =  new  parserFront(curParam->lensX1,   curParam->lensX2,   7, 27, 30);
    parseRetina =  new  parserFront(curParam->retinaX1, curParam->retinaX2, 7, 54, 0);

    for(int i=0; i<Sample->count(); i++)
    {
        tmp=parseCornea->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!corneaEn)
                measureParam->Cornea = tmp;
            corneaEn = true;
            extremum->append(tmp);
        }

        tmp=parseLens->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!lens1En)
            {
                measureParam->L1 = tmp;
                lens1En = true;
            }
            else
            {
                if(!lens2En)
                {
                    measureParam->L2 = tmp;
                    lens2En = true;
                }
            }
            extremum->append(tmp);
        }

        tmp=parseRetina->parser(i,Sample->at(i)*2);
        if(tmp>=0)
        {
            if(!retinaEn)
                measureParam->Retina = tmp;
            retinaEn = true;
            extremum->append(tmp);
        }
    }

    if((curParam->regimCataract == REGIM::APHAKIC)||(curParam->regimMeasure == REGIM::MANUAL))
    {
        if (corneaEn && retinaEn)
            bValid = true;
    }
    else
    {
        if (corneaEn && lens1En && lens2En && retinaEn)
        {
            bValid = true;
            qDebug()<<"measureParam->L2"<<measureParam->L2;
            qDebug()<<"measureParam->Retine"<<measureParam->Retina;
            for(int i=(measureParam->L2+50); i<=(measureParam->Retina-10); i++)
            {
//                qDebug()<<i<<(unsigned char)Sample->at(i);
                if(((unsigned char)Sample->at(i))>50)
                    bValid = false;
            }
        }
    }

    if(bValid)
        calculateParam(measureParam);

    return (bValid);
}

void Parcer::calculateParam(stMeasureParam *measureParam)
{
    if(curParam->regimContact == REGIM::CONTACT)
        measureParam->Cornea = 4;
    measureParam->ALave  = decRound(measureParam->Retina - measureParam->Cornea, 2, 1555);
    measureParam->ACD    = decRound(measureParam->L1 - measureParam->Cornea,     2, 1534);
    measureParam->LT     = decRound(measureParam->L2 - measureParam->L1,         2, 1641);
    measureParam->VIT    = decRound(measureParam->Retina - measureParam->L2,     2, 1532);
    measureParam->AL     = measureParam->ACD + measureParam->LT + measureParam->VIT;
}

double Parcer::decRound(double Val, quint8 dec, quint16 speed)
{
    double koef = 1.0;
    koef /= speed;
    koef *= 2000000;
    koef /= 50;

    Val *= pow(10, dec);
    Val /= koef;
    Val =  round(Val);
    Val /= pow(10, dec);
    return Val;
}
