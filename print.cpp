#include "print.h"
#include "mainwindow.h"
#include <qwt_plot_renderer.h>
//#include <QAbstractItemModel>
#include <QTabWidget>
#include "calclens.h"

Print::Print(QWidget *parent, CurParam *link) : QWidget(parent)
{
    curParam = link;
}

void Print::doPreview()
{
    stMeasureParam measureParam;
    quint8 kolvo = 0;
    QwtPlotRenderer renderer;
    QModelIndexList lsSelect;
    QModelIndex index;
    quint8 rowCount = twMeas->model()->rowCount();

    for(quint8 i=0; i<rowCount; i++)
    {
        index = twMeas->model()->index(i,6);
        if(twMeas->model()->data(index, Qt::DisplayRole).toBool())
            lsSelect << index;
    }

    QPixmap pix1(750, 600);
    QPainter *painter1 = new QPainter(&pix1);
    QPixmap pix2(750, 600);
    QPainter *painter2 = new QPainter(&pix2);
    QPixmap pix3(750, 600);
    QPainter *painter3 = new QPainter(&pix3);
    QPixmap pix4(750, 600);
    QPainter *painter4 = new QPainter(&pix4);

    pix1.fill(QColor(Qt::white));
    pix2.fill(QColor(Qt::white));
    pix3.fill(QColor(Qt::white));
    pix4.fill(QColor(Qt::white));

    al1=al2=al3=al4=acd1=acd2=acd3=acd4=0;

    foreach (index, lsSelect)
    {
        index = twMeas->model()->index(kolvo, 0);
        measureParam.Sample = twMeas->model()->data(index, roleSample).toByteArray();
        measureParam.Cornea = twMeas->model()->data(index, roleCornea).toDouble();
        measureParam.L1 =     twMeas->model()->data(index, roleL1).toDouble();
        measureParam.L2 =     twMeas->model()->data(index, roleL2).toDouble();
        measureParam.Retina = twMeas->model()->data(index, roleRetina).toDouble();

        switch (kolvo)
        {
        case 0:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter1, QRectF(0, 0, 750, 600));
            index = twMeas->model()->index(kolvo, 1);
            al1   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            index = twMeas->model()->index(kolvo, 3);
            acd1  = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            break;
        case 1:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter2, QRectF(0, 0, 750, 600));
            index = twMeas->model()->index(kolvo, 1);
            al2   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            index = twMeas->model()->index(kolvo, 3);
            acd2  = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            break;
        case 2:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter3, QRectF(0, 0, 750, 600));
            index = twMeas->model()->index(kolvo, 1);
            al3   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            index = twMeas->model()->index(kolvo, 3);
            acd3  = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            break;
        case 3:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter4, QRectF(0, 0, 750, 600));
            index = twMeas->model()->index(kolvo, 1);
            al4   = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            index = twMeas->model()->index(kolvo, 3);
            acd4  = twMeas->model()->data(index, Qt::DisplayRole).toDouble();
            break;
        }
        kolvo++;
    }



    //    QTabWidget *mw;
    //    calculator *cl;
    //    CalcLensTable *cLens;
    //    qDebug()<<"name"<<this->parent()->parent()->objectName();
    //    mw = (QTabWidget*)this->parent()->parent();
    //    cl = (calculator*)mw->widget(2);
    //    cLens = cl->calcLens->lensTable;






    painter1->end();
    painter2->end();
    painter3->end();
    painter4->end();

    //    qDebug()<<"pix.size()"<<pix.size();

    iPlot1 = pix1.toImage();
    iPlot2 = pix2.toImage();
    iPlot3 = pix3.toImage();
    iPlot4 = pix4.toImage();

    QString fileName = ":/test/report";
    report = new QtRPT(this);

    //    report->setBackgroundImage((QPixmap)pix);

    report->loadReport(fileName);
    report->recordCount << 7;

    QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));

    QObject::connect(report, SIGNAL(setValueImage(int,QString,QImage&,int)),
                     this, SLOT(setValueImage(int,QString,QImage&,int)));

    //    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
    //                     this, SLOT(setValueImage(int&, QString&, QImage&, int)));

    report->printExec(true);



}



void Print::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
    QString paramTmp;
    Q_UNUSED(reportPage);
    Q_UNUSED(recNo);

    if(paramName == "measureParam1")
    {
        if((al1>0)&&(acd1>0))
        {
            paramTmp.append(QString("AL: %1   ACD:%2").arg(al1).arg(acd1));
            paramValue = paramTmp;
        }
    }

    if(paramName == "measureParam2")
    {
        if((al2>0)&&(acd2>0))
        {
            paramTmp.append(QString("AL: %1   ACD:%2").arg(al2).arg(acd2));
            paramValue = paramTmp;
        }
    }

    if(paramName == "measureParam3")
    {
        if((al3>0)&&(acd3>0))
        {
            paramTmp.append(QString("AL: %1   ACD:%2").arg(al3).arg(acd3));
            paramValue = paramTmp;
        }
    }

    if(paramName == "measureParam4")
    {
        if((al4>0)&&(acd4>0))
        {
            paramTmp.append(QString("AL: %1   ACD:%2").arg(al4).arg(acd4));
            paramValue = paramTmp;
        }
    }

    if (paramName == "doctor")
        paramValue = curParam->doctorName;
    if (paramName == "name")
        paramValue = curParam->patientName;
    if (paramName == "id")
        paramValue = curParam->patientId;
    if (paramName == "birth")
        paramValue = curParam->birthDate;
    if (paramName == "al")
        paramValue = QString::number(curParam->ALave, 'f', 2);
    if (paramName == "acd")
        paramValue = QString::number(curParam->ACD,   'f', 2);

    if (paramName == "side")
        paramValue = (curParam->regimSide==REGIM::OD)?"OD\r\nright":"OS\r\nleft";
    if (paramName == "k1")
        paramValue = (curParam->regimSide==REGIM::OD)?QString::number(curParam->k1left, 'f', 2):QString::number(curParam->k1right, 'f', 2);
    if (paramName == "k2")
        paramValue = (curParam->regimSide==REGIM::OD)?QString::number(curParam->k2left, 'f', 2):QString::number(curParam->k2right, 'f', 2);

    if (paramName == "rx")
        paramValue = curParam->Rx;//1;//personalParam.Rx;

    if (paramName.indexOf("IOL1")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila1->twFormula->model();//(QStandardItemModel*)Formula1->twFormula->model();
        if(paramName.indexOf("11")>0)
            index = model->index(0, 1);
        if(paramName.indexOf("12")>0)
            index = model->index(1, 1);
        if(paramName.indexOf("13")>0)
            index = model->index(2, 1);
        if(paramName.indexOf("14")>0)
            index = model->index(3, 1);
        if(paramName.indexOf("15")>0)
            index = model->index(4, 1);
        if(paramName.indexOf("16")>0)
            index = model->index(5, 1);
        if(paramName.indexOf("17")>0)
            index = model->index(6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName.indexOf("Ref1")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila1->twFormula->model();
        if(paramName.indexOf("11")>0)
            index = model->index(0, 2);
        if(paramName.indexOf("12")>0)
            index = model->index(1, 2);
        if(paramName.indexOf("13")>0)
            index = model->index(2, 2);
        if(paramName.indexOf("14")>0)
            index = model->index(3, 2);
        if(paramName.indexOf("15")>0)
            index = model->index(4, 2);
        if(paramName.indexOf("16")>0)
            index = model->index(5, 2);
        if(paramName.indexOf("17")>0)
            index = model->index(6, 2);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName.indexOf("IOL2")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila2->twFormula->model();
        if(paramName.indexOf("21")>0)
            index = model->index(0, 1);
        if(paramName.indexOf("22")>0)
            index = model->index(1, 1);
        if(paramName.indexOf("23")>0)
            index = model->index(2, 1);
        if(paramName.indexOf("24")>0)
            index = model->index(3, 1);
        if(paramName.indexOf("25")>0)
            index = model->index(4, 1);
        if(paramName.indexOf("26")>0)
            index = model->index(5, 1);
        if(paramName.indexOf("27")>0)
            index = model->index(6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName.indexOf("Ref2")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila2->twFormula->model();
        if(paramName.indexOf("21")>0)
            index = model->index(0, 2);
        if(paramName.indexOf("22")>0)
            index = model->index(1, 2);
        if(paramName.indexOf("23")>0)
            index = model->index(2, 2);
        if(paramName.indexOf("24")>0)
            index = model->index(3, 2);
        if(paramName.indexOf("25")>0)
            index = model->index(4, 2);
        if(paramName.indexOf("26")>0)
            index = model->index(5, 2);
        if(paramName.indexOf("27")>0)
            index = model->index(6, 2);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName.indexOf("IOL3")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila3->twFormula->model();
        if(paramName.indexOf("31")>0)
            index = model->index(0, 1);
        if(paramName.indexOf("32")>0)
            index = model->index(1, 1);
        if(paramName.indexOf("33")>0)
            index = model->index(2, 1);
        if(paramName.indexOf("34")>0)
            index = model->index(3, 1);
        if(paramName.indexOf("35")>0)
            index = model->index(4, 1);
        if(paramName.indexOf("36")>0)
            index = model->index(5, 1);
        if(paramName.indexOf("37")>0)
            index = model->index(6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName.indexOf("Ref3")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila3->twFormula->model();
        if(paramName.indexOf("31")>0)
            index = model->index(0, 2);
        if(paramName.indexOf("32")>0)
            index = model->index(1, 2);
        if(paramName.indexOf("33")>0)
            index = model->index(2, 2);
        if(paramName.indexOf("34")>0)
            index = model->index(3, 2);
        if(paramName.indexOf("35")>0)
            index = model->index(4, 2);
        if(paramName.indexOf("36")>0)
            index = model->index(5, 2);
        if(paramName.indexOf("37")>0)
            index = model->index(6, 2);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName == "exact1")
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila1->twEmm->model();
        index = model->index(Formila1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName == "exact2")
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila2->twEmm->model();
        index = model->index(Formila1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName == "exact3")
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formila3->twEmm->model();
        index = model->index(Formila1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName == "lens1")
    {
        paramTmp = "lens: ";
        paramTmp.append(Formila1->lLens->text());
        paramValue = paramTmp;
    }
    if (paramName == "lens2")
    {
        paramTmp = "lens: ";
        paramTmp.append(Formila2->lLens->text());
        paramValue = paramTmp;
    }
    if (paramName == "lens3")
    {
        paramTmp = "lens: ";
        paramTmp.append(Formila3->lLens->text());
        paramValue = paramTmp;
    }

    if (paramName == "formula1")
        paramValue = Formila1->cbFormula->currentText();
    if (paramName == "formula2")
        paramValue = Formila2->cbFormula->currentText();
    if (paramName == "formula3")
        paramValue = Formila3->cbFormula->currentText();
    if (paramName == "regimMeasure")
    {
        switch(curParam->regimMeasure)
        {
        case REGIM::AUTOFREEZ: paramTmp = "AutoFreez/ "; break;
        case REGIM::AUTO:      paramTmp = "Auto/ "; break;
        case REGIM::MANUAL:    paramTmp = "Manual/ "; break;
        }
        switch(curParam->regimContact)
        {
        case REGIM::CONTACT:   paramTmp.append("Contact/ "); break;
        case REGIM::IMMERSION: paramTmp.append("Immersion/ "); break;
        }
        switch(curParam->regimCataract)
        {
        case REGIM::CATARACT: paramTmp.append("Cataract/"); break;
        case REGIM::APHAKIC:  paramTmp.append("Aphakic/"); break;
        }
        paramTmp.append((curParam->regimSide==REGIM::OD)?"OD right":"OS left");
        paramValue = paramTmp;
    }
    if (paramName == "measureParam")
    {
        paramTmp.append(QString("AL: %1   ACD:%2").arg(curParam->ALave).arg(curParam->ACD));
        paramValue = paramTmp;
    }

    if (paramName == "date")
    {
        //        paramTmp.append(QString("AL: %1   ACD:%2").arg(curParam->ALave).arg(curParam->ACD));
        paramValue = curParam->curTime.toString("MM.dd.yyyy hh:mm:ss");
    }

}

void Print::setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage)
{
    if (paramName == "image1")
        paramValue = iPlot1;
    if (paramName == "image2")
        paramValue = iPlot2;
    if (paramName == "image3")
        paramValue = iPlot3;
    if (paramName == "image4")
        paramValue = iPlot4;
}

