#include "calculator.h"
#include "calc.h"
#include <adjview.h>
#include <QDebug>
#include <qwt_plot_renderer.h>
#include <QAbstractItemModel>

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
//    columnPercent<<20<<20<<20<<20<<20;
    columnPercent<<20<<15<<10<<10<<0<<21<<8<<8<<8;
//    lst<<"Lens Name"<<"AConst"<<"ACD"<<"SF"<<"FORMULA";
    lst<<"Lens Name"<<"AConst"<<"ACD"<<"SF"<<"FORMULA"<<"id"<<"A1"<<"A2"<<"A3";

    twLens = new adjview(3, lst, columnPercent);
    twLens->setMinimumWidth(350);
    modelMainLens = curParam->lensModel;
    twLens->setModel(modelMainLens);
//    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
//    modelMainLens->setHeaderData(1, Qt::Horizontal, "AConst", Qt::DisplayRole);
//    modelMainLens->setHeaderData(2, Qt::Horizontal, "ACD", Qt::DisplayRole);
//    modelMainLens->setHeaderData(3, Qt::Horizontal, "SF", Qt::DisplayRole);
//    modelMainLens->setHeaderData(4, Qt::Horizontal, "FORMULA", Qt::DisplayRole);
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

    frCalculator = new QFrame();
    frCalculator->setFrameShape(QFrame::WinPanel);
    frCalculator->setFrameShadow(QFrame::Raised);
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

}

void calculator::refreshFormuls()
{
    stPersonalParam personalParam;
    quint8 nFormula;
    QString lensName, lensAconst, lensAcd, lensFs;

    personalParam = pCalcPatient->getPersonalParam();





    if(!((curParam->ACD>0)&&(curParam->ALave>0)&&(curParam->K>0)))
        return;

    Formula1->setEnabled(false);
    Formula2->setEnabled(false);
    Formula3->setEnabled(false);



    if(twLens->model()->rowCount()>0)
    {
        for(quint8 i=0; i<twLens->model()->rowCount() && i<3; i++)
        {
            nFormula   = twLens->model()->itemData(twLens->model()->index(i,4)).value(0).toInt();
            lensName   = twLens->model()->itemData(twLens->model()->index(i,0)).value(0).toString();

            if(personalParam.AConst>0)
                lensAconst = QString("%1").arg(personalParam.AConst);
            else
                lensAconst = twLens->model()->itemData(twLens->model()->index(i,1)).value(0).toString();

            if(personalParam.ACD>0)
                lensAcd = QString("%1").arg(personalParam.ACD);
            else
                lensAcd = twLens->model()->itemData(twLens->model()->index(i,2)).value(0).toString();

            if(personalParam.SF>0)
                lensFs = QString("%1").arg(personalParam.SF);
            else
                lensFs = twLens->model()->itemData(twLens->model()->index(i,3)).value(0).toString();





            switch (i)
            {
            case 0:
                Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, curParam->K, curParam->ALave, curParam->ACD);
                Formula1->setEnabled(true);
                break;
            case 1:
                Formula2->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, curParam->K, curParam->ALave, curParam->ACD);
                Formula2->setEnabled(true);
                break;
            case 2:
                Formula3->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, curParam->K, curParam->ALave, curParam->ACD);
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
        Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, curParam->K, curParam->ALave, curParam->ACD);
        Formula1->setEnabled(true);
    }
}

void calculator::refreshMeasure()
{
    pCalcPatient->refreshMeasure();
}

void calculator::printPreview()
{
    QPrinter             printer( QPrinter::HighResolution );
    printer.setPageSize(QPrinter::A4);
//    QPrintPreviewDialog  preview( &printer, this );
      QPrintPreviewDialog  preview( &printer);
    connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    preview.exec();
}

void calculator::print( QPrinter* printer )
{
    QByteArray sample;
    QModelIndex index;
    QModelIndexList lsSelect;
    quint8 kolvo = 0;

    QPainter painter( printer );
    lsSelect = twMeas->selectionModel()->selectedRows();
    QwtPlotRenderer renderer;

    foreach (index, lsSelect)
    {
        index = twMeas->model()->index(kolvo, 0);
        sample = twMeas->model()->data(index, roleSample).toByteArray();
        switch (kolvo)
        {
        case 0:
            pPlotPrint1 = new Plot(this, true, curParam);
            pPlotPrint1->drawSample(&sample);
            pPlotPrint1->enableAxis(QwtPlot::xTop,false);
            pPlotPrint1->enableAxis(QwtPlot::xBottom,true);
            pPlotPrint1->enableAxis(QwtPlot::yLeft,true);
            pPlotPrint1->replot();
            renderer.render(pPlotPrint1, &painter, QRectF(500,1000,2000,1800));
            break;
        case 1:
            pPlotPrint2 = new Plot(this, true, curParam);
            pPlotPrint2->drawSample(&sample);
            pPlotPrint2->enableAxis(QwtPlot::xTop,false);
            pPlotPrint2->enableAxis(QwtPlot::xBottom,true);
            pPlotPrint2->enableAxis(QwtPlot::yLeft,true);
            pPlotPrint2->replot();
            renderer.render(pPlotPrint2, &painter, QRectF(2700,1000,2000,1800));
            break;
        case 2:
            pPlotPrint3 = new Plot(this, true, curParam);
            pPlotPrint3->drawSample(&sample);
            pPlotPrint3->enableAxis(QwtPlot::xTop,false);
            pPlotPrint3->enableAxis(QwtPlot::xBottom,true);
            pPlotPrint3->enableAxis(QwtPlot::yLeft,true);
            pPlotPrint3->replot();
            renderer.render(pPlotPrint3, &painter, QRectF(500,3000,2000,1800));
            break;
        }
        kolvo++;
    }

    painter.drawRect(500, 200, 4000, 400);
    QFont    font = painter.font();
    font.setPixelSize(80);
    painter.setFont( font );
    QRect    page0( 500, 200, 500, 400);
    painter.drawText(page0, Qt::AlignRight, "Name:\r\nID:\r\nDate of Birth:\r\nExam Date:" );
    font.setBold(true);
    painter.setFont( font );

    QRect    page1( 1000, 200, 500, 400);
    QString  sPatient;
    sPatient.append(QString("%1\r\n%2").arg(curParam->patientName).arg(curParam->patientId));
    painter.drawText(page1, Qt::AlignLeft, sPatient);

//    QRect    page1(1000, 200, 1000, 400);
//    pModel1 = Formula1->getModel();
//    pModel2 = Formula2->getModel();
//    pModel3 = Formula3->getModel();

//    int kolLine = 0;
#define kolColumn  3
#define hightLine  100
#define yPosTable  5000
#define xPosTable  500
#define widthTable 3900

//    QSize size;
//    size.setHeight(20000);
//    size.setWidth (20000);
    if(Formula1->isEnabled())
    {
        QPixmap pixmap(Formula1->size());
        Formula1->render(&pixmap);
        painter.drawPixmap(2700,3000,2000,1800,pixmap);
    }

    if(Formula2->isEnabled())
    {
        QPixmap pixmap(Formula2->size());
        Formula2->render(&pixmap);
        painter.drawPixmap(500,5000,2000,1800,pixmap);
    }

    if(Formula3->isEnabled())
    {
        QPixmap pixmap(Formula3->size());
        Formula3->render(&pixmap);
        painter.drawPixmap(2700,5000,2000,1800,pixmap);
    }

//    QRect    txt1(xPosTable+(widthTable/(kolColumn*2))*0, yPosTable+(0+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//    QRect    txt2(xPosTable+(widthTable/(kolColumn*2))*1, yPosTable+(+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//    painter.drawText(txt1, Qt::AlignCenter, curParam->patientName);
//    painter.drawText(txt2, Qt::AlignCenter, pModel1->model->data(pModel1->model->index(i, 1), Qt::DisplayRole).toString());

//    kolLine = qMax(pModel1->model->rowCount(), pModel2->model->rowCount());
//    kolLine = qMax(kolLine, pModel3->model->rowCount());

//    for(quint8 i=0; i<kolLine; i++)
//    {
//        painter.drawRect(xPosTable, yPosTable+i*hightLine, widthTable, hightLine);
//    }

//    for(quint8 i=0; i<kolColumn; i++)
//    {
//        painter.drawRect(xPosTable+((widthTable/kolColumn)*i), yPosTable, (widthTable/kolColumn), kolLine*hightLine);
//    }

//    for(quint8 i=0; i<(kolColumn*2); i++)
//    {
//        painter.drawRect(xPosTable+(widthTable/(kolColumn*2)*i), yPosTable+hightLine, (widthTable/(kolColumn*2)), (kolLine-1)*hightLine);
//    }

//    for (quint8 i=0; i<pModel1->model->rowCount(); i++)
//    {
//        QRect    txt1(xPosTable+(widthTable/(kolColumn*2))*0, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        QRect    txt2(xPosTable+(widthTable/(kolColumn*2))*1, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        painter.drawText(txt1, Qt::AlignCenter, pModel1->model->data(pModel1->model->index(i, 0), Qt::DisplayRole).toString());
//        painter.drawText(txt2, Qt::AlignCenter, pModel1->model->data(pModel1->model->index(i, 1), Qt::DisplayRole).toString());
//    }

//    for (quint8 i=0; i<pModel2->model->rowCount(); i++)
//    {
//        QRect    txt1(xPosTable+(widthTable/(kolColumn*2))*2, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        QRect    txt2(xPosTable+(widthTable/(kolColumn*2))*3, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        painter.drawText(txt1, Qt::AlignCenter, pModel2->model->data(pModel2->model->index(i, 0), Qt::DisplayRole).toString());
//        painter.drawText(txt2, Qt::AlignCenter, pModel2->model->data(pModel2->model->index(i, 1), Qt::DisplayRole).toString());
//    }

//    for (quint8 i=0; i<pModel3->model->rowCount(); i++)
//    {
//        QRect    txt1(xPosTable+(widthTable/(kolColumn*2))*4, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        QRect    txt2(xPosTable+(widthTable/(kolColumn*2))*5, yPosTable+(i+3)*hightLine, (widthTable/(kolColumn*2)), 100);
//        painter.drawText(txt1, Qt::AlignCenter, pModel3->model->data(pModel3->model->index(i, 0), Qt::DisplayRole).toString());
//        painter.drawText(txt2, Qt::AlignCenter, pModel3->model->data(pModel3->model->index(i, 1), Qt::DisplayRole).toString());
//    }
}

void calculator::refreshLens(QSqlQueryModel *link)
{
    twLens->setModel(link);
}

void calculator::updatePatient()
{
    pCalcPatient->updatePatient();
}
