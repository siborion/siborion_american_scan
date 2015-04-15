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
//    QByteArray sample;
    QModelIndexList lsSelect;
    QModelIndex index;
    lsSelect = twMeas->selectionModel()->selectedRows();

//    QPixmap pix("qt.png");// = new QPixmap(1000,1000);
    QPixmap pix(2100, 2970);
    QPainter *painter = new QPainter(&pix);
    pix.fill(QColor(Qt::white));
//    painter->setBackground()

//    painter->drawLine(0,0,200,200);
//    painter->drawText(200,200,"999999999");

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
            renderer.render(pPlotPrint1, painter, QRectF(100,  600, 900, 900));
            break;
        case 1:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter, QRectF(1100, 600, 900, 900));
            break;
        case 2:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter, QRectF(100,  1600, 900, 900));
            break;
        case 3:
            pPlotPrint1 = new PrintPlot(this, curParam, &measureParam.Sample);
            pPlotPrint1->updateSample(&measureParam, true);
            renderer.render(pPlotPrint1, painter, QRectF(1100, 1600, 900, 900));
            break;
        }
        kolvo++;
    }

    painter->end();

    qDebug()<<"pix.size()"<<pix.size();

    QString fileName = "example9.xml";
    QtRPT *report = new QtRPT(this);

    report->setBackgroundImage((QPixmap)pix);

    report->loadReport(fileName);
    report->recordCount << 2;

//    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)), this, SLOT(setValue(int&, QString&, QVariant&, int)));
    QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));


    report->printExec(true);




//    QPrinter             printer( QPrinter::HighResolution );
//    printer.setPageSize(QPrinter::A4);
//    QPrintPreviewDialog  preview( &printer);
//    connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
//    preview.showFullScreen();
//    preview.exec();
}

void calculator::print( QPrinter* printer )
{
    QByteArray sample;
    QModelIndex index;
    QModelIndexList lsSelect;
    quint8 kolvo = 0;

    QPixmap *pix = new QPixmap(500,500);
//    scene->addPixmap(*pix);

    QPainter *paint = new QPainter(pix);


//    QPixmap tt;
//    qDebug()<<"000";
    QPainter painter;
//    qDebug()<<"444";
    QwtPlotRenderer renderer;
    QString fileName = "example9.xml";
    QtRPT *report = new QtRPT(this);
    report->loadReport(fileName);
    report->recordCount << 2;

//    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
//                     this, SLOT(setValue(int&, QString&, QVariant&, int)));


//    foreach (index, lsSelect)
//    {
//        index = twMeas->model()->index(kolvo, 0);
//        sample = twMeas->model()->data(index, roleSample).toByteArray();
//        switch (kolvo)
//        {
//        case 0:
//            pPlotPrint1 = new PrintPlot(this, curParam, &sample);
//            renderer.render(pPlotPrint1, &painter, QRectF(500,1000,2000,1800));
//            break;
//        case 1:
//            pPlotPrint1 = new PrintPlot(this, curParam, &sample);
//            renderer.render(pPlotPrint1, &painter, QRectF(2700,1000,2000,1800));
//            break;
//        case 2:
//            pPlotPrint1 = new PrintPlot(this, curParam, &sample);
//            renderer.render(pPlotPrint1, &painter, QRectF(500,3000,2000,1800));
//            break;
//        case 3:
//            pPlotPrint1 = new PrintPlot(this, curParam, &sample);
//            renderer.render(pPlotPrint1, &painter, QRectF(2700,3000,2000,1800));
//            break;
//        }
//        kolvo++;
//    }
    qDebug()<<"111";
//    report->setBackgroundImage(pix);
//    report->drawBackground(&painter);
//    report->setBackgroundImage(QPixmap("qt.png"));

//    QObject::connect(report, SIGNAL(setValue(const int, const QString, QVariant&, const int)),
//                     this, SLOT(setValue(const int, const QString, QVariant&, const int)));
//    QObject::connect(report, SIGNAL(setValueImage(const int, const QString, QImage&, const int)),
//                     this, SLOT(setValueImage(const int, const QString, QImage&, const int)));


    qDebug()<<"222";
    report->printExec();
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
    Q_UNUSED(reportPage);
    Q_UNUSED(recNo);
    if (paramName == "ttt")
        paramValue = "8888";
    qDebug()<<paramName;
}

//void calculator::setValueImage(const int recNo, const QString paramName, QImage &paramValue, const int reportPage) {
//    Q_UNUSED(recNo);
//    Q_UNUSED(reportPage);
//    if (paramName == "image") {
//        QImage *image = new QImage(QCoreApplication::applicationDirPath()+"/qt.png");
//        paramValue = *image;
//    }
//}
