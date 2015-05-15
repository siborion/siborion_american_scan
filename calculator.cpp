#include "calculator.h"
#include "calc.h"
#include <adjview.h>
#include <QDebug>
#include <qwt_plot_renderer.h>
#include <QAbstractItemModel>
#include "qtrpt.h"
#include <QCoreApplication>

calculator::calculator(QWidget *parent, CurParam *link) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;

    curParam = link;

    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();

    columnPercent.clear();
    columnPercent<<50<<50;
    twName = new adjview(3, 2, columnPercent);
    model = (QStandardItemModel*)twName->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapName[i]));
        model->setItem(i, 1, new QStandardItem());
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }



    //-------------------------------
    columnPercent.clear();
    columnPercent<<20<<0<<21<<15<<10<<10<<8<<8<<8;
    lst<<"Lens Name"<<"id"<<"Formula"<<"AConst"<<"ACD"<<"SF"<<"A0"<<"A1"<<"A2";

    twLens = new adjview(3, lst, columnPercent);
    twLens->setMinimumWidth(350);
//    twLens->setFrameStyle(QFrame::Box);
//    modelMainLens = curParam->lensModel;
//    twLens->setModel(modelMainLens);
    refreshLens(curParam->lensModel);
    //-------------------------------
    columnPercent.clear();
    columnPercent<<40<<40<<20;
    twK = new adjview(5, 3, columnPercent);
    model = (QStandardItemModel*)twK->model();
    for(quint8 i=0; i<5; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapK[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
        model->item   (i, 0)->setEnabled(false);
        model->setItem(i, 2, i==0?new QStandardItem("mm"):new QStandardItem("D"));
        model->item   (i, 2)->setBackground(Qt::lightGray);
        model->item   (i, 2)->setEditable(false);
        model->item   (i, 2)->setEnabled(false);
    }



    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    twK->setPalette(palette);

    pCalcPatient = new calculator_patient(this, link);



    columnPercent.clear();
    columnPercent<<50<<50;
    twA = new adjview(3, 2, columnPercent);
    model = (QStandardItemModel*)twA->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapA[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }

    twRx = new adjview(1, 2, columnPercent);
    model = (QStandardItemModel*)twRx->model();
    model->setItem(0, 0, new QStandardItem(baseMapA[3]));
    model->item   (0, 0)->setBackground(Qt::lightGray);
    model->item   (0, 0)->setEditable(false);

    pbPrint = new QPushButton("Print");



    layoutTop->addWidget(pCalcPatient);
    layoutTop->addWidget(twLens);
    layout->addLayout(layoutTop);

    frCalculator = new QWidget();
//    frCalculator->setFrameShape(QFrame::WinPanel);
//    frCalculator->setFrameShadow(QFrame::Raised);
    QHBoxLayout *frLayout = new QHBoxLayout(frCalculator);

    Formula1 = new formula();
    Formula2 = new formula();
    Formula3 = new formula();

    frLayout->addWidget(Formula1);
    frLayout->addWidget(Formula2);
    frLayout->addWidget(Formula3);

    layout->addWidget(frCalculator);
    layout->addWidget(pbPrint);

    connect(pCalcPatient, SIGNAL(refreshFormula()), SLOT(refreshFormuls()));
    connect(pbPrint, SIGNAL(clicked()), SLOT(printPreview()));
    connect(pCalcPatient, SIGNAL(changeSideCalculator()), SLOT(changeSideCalculatorSlot()));

}

void calculator::refreshFormuls()
{
    stPersonalParam personalParam;
    quint8 nFormula;
    QString lensName, lensAconst, lensAcd, lensFs, lensA0, lensA1, lensA2;

    personalParam = pCalcPatient->getPersonalParam();

    Formula1->clear();
    Formula2->clear();
    Formula3->clear();

    if(!((curParam->ACD>0)&&(curParam->ALave>0)&&(curParam->K>0)))
        return;

    Formula1->setEnabled(false);
    Formula2->setEnabled(false);
    Formula3->setEnabled(false);


    if(twLens->model()->rowCount()>0)
    {
        for(quint8 i=0; i<twLens->model()->rowCount() && i<3; i++)
        {
            nFormula   = twLens->model()->itemData(twLens->model()->index(i,1)).value(0).toInt();
            lensName   = twLens->model()->itemData(twLens->model()->index(i,0)).value(0).toString();

            if(personalParam.AConst>0)
                lensAconst = QString("%1").arg(personalParam.AConst);
            else
                lensAconst = twLens->model()->itemData(twLens->model()->index(i,3)).value(0).toString();

            if(personalParam.ACD>0)
                lensAcd = QString("%1").arg(personalParam.ACD);
            else
                lensAcd = twLens->model()->itemData(twLens->model()->index(i,4)).value(0).toString();

            if(personalParam.SF>0)
                lensFs = QString("%1").arg(personalParam.SF);
            else
                lensFs = twLens->model()->itemData(twLens->model()->index(i,5)).value(0).toString();

            lensA0 =  twLens->model()->itemData(twLens->model()->index(i,6)).value(0).toString();
            lensA1 =  twLens->model()->itemData(twLens->model()->index(i,7)).value(0).toString();
            lensA2 =  twLens->model()->itemData(twLens->model()->index(i,8)).value(0).toString();


            switch (i)
            {
            case 0:
                Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, lensA0, lensA1, lensA2, curParam->K, curParam->ALave, curParam->ACD, personalParam.Rx);
                Formula1->setEnabled(true);
                break;
            case 1:
                Formula2->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, lensA0, lensA1, lensA2, curParam->K, curParam->ALave, curParam->ACD, personalParam.Rx);
                Formula2->setEnabled(true);
                break;
            case 2:
                Formula3->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, lensA0, lensA1, lensA2, curParam->K, curParam->ALave, curParam->ACD, personalParam.Rx);
                Formula3->setEnabled(true);
            default:
                break;
            }
        }
    }
    else
    {
        nFormula = 1;
        lensName   = "no Name";
        if(personalParam.AConst>0)
            lensAconst = QString("%1").arg(personalParam.AConst);
        if(personalParam.ACD>0)
            lensAcd = QString("%1").arg(personalParam.ACD);
        if(personalParam.SF>0)
            lensFs = QString("%1").arg(personalParam.SF);
        Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, lensA0, lensA1, lensA2, curParam->K, curParam->ALave, curParam->ACD, personalParam.Rx);
        Formula1->setEnabled(true);
    }
}

void calculator::refreshMeasure()
{
    pCalcPatient->refreshMeasure();
}

void calculator::printPreview()
{
    stMeasureParam measureParam;

    quint8 kolvo = 0;
    QwtPlotRenderer renderer;
    QModelIndexList lsSelect;
    QModelIndex index;
    lsSelect = twMeas->selectionModel()->selectedRows();

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
    QtRPT *report = new QtRPT(this);

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


void calculator::refreshLens(QSqlQueryModel *link)
{
    qDebug()<<"twLens->setModel(link)";
    twLens->setModel(link);
    link->setHeaderData(0, Qt::Horizontal, "Lens", Qt::DisplayRole);
    link->setHeaderData(1, Qt::Horizontal, "numF", Qt::DisplayRole);
    link->setHeaderData(2, Qt::Horizontal, "Formula", Qt::DisplayRole);
    link->setHeaderData(3, Qt::Horizontal, "AConst", Qt::DisplayRole);
    link->setHeaderData(4, Qt::Horizontal, "ACD", Qt::DisplayRole);
    link->setHeaderData(5, Qt::Horizontal, "SF", Qt::DisplayRole);
}

void calculator::updatePatient()
{
    pCalcPatient->updatePatient();
}

void calculator::changeSideCalculatorSlot()
{
    emit changeSideCalculator();
}

void calculator::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
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

    if (paramName == "name")
        paramValue = curParam->patientName;
    if (paramName == "id")
        paramValue = curParam->patientId;
    if (paramName == "birth")
        paramValue = curParam->birthDate;
    if (paramName == "al")
        paramValue = curParam->ALave;
    if (paramName == "acd")
        paramValue = curParam->ACD;




    if (paramName == "side")
        paramValue = (curParam->regimSide==REGIM::OD)?"OD\r\nright":"OS\r\nleft";
    if (paramName == "k1")
        paramValue = (curParam->regimSide==REGIM::OD)?curParam->k1left:curParam->k1right;
    if (paramName == "k2")
        paramValue = (curParam->regimSide==REGIM::OD)?curParam->k2left:curParam->k2right;
    if (paramName == "rx")
    {
        stPersonalParam personalParam;
        personalParam = pCalcPatient->getPersonalParam();
        paramValue = personalParam.Rx;
    }

    if (paramName.indexOf("IOL1")>=0)
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formula1->twFormula->model();
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
        model = (QStandardItemModel*)Formula1->twFormula->model();
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
        model = (QStandardItemModel*)Formula2->twFormula->model();
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
        model = (QStandardItemModel*)Formula2->twFormula->model();
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
        model = (QStandardItemModel*)Formula3->twFormula->model();
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
        model = (QStandardItemModel*)Formula1->twFormula->model();
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
        model = (QStandardItemModel*)Formula1->twEmm->model();
        index = model->index(Formula1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName == "exact2")
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formula2->twEmm->model();
        index = model->index(Formula1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }
    if (paramName == "exact3")
    {
        QStandardItemModel *model;
        QModelIndex index;
        model = (QStandardItemModel*)Formula3->twEmm->model();
        index = model->index(Formula1->cbFormula->currentIndex()+6, 1);
        paramValue = model->data(index, Qt::DisplayRole);
    }

    if (paramName == "lens1")
        paramValue = Formula1->lLens->text();
    if (paramName == "lens2")
        paramValue = Formula2->lLens->text();
    if (paramName == "lens3")
        paramValue = Formula3->lLens->text();

    if (paramName == "formula1")
        paramValue = Formula1->cbFormula->currentText();
    if (paramName == "formula2")
        paramValue = Formula2->cbFormula->currentText();
    if (paramName == "formula3")
        paramValue = Formula3->cbFormula->currentText();
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
}

void calculator::setValueImage(int recNo, QString paramName, QImage &paramValue,int reportPage)
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
