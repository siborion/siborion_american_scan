#include "calculator.h"
#include "calc.h"
#include <QDebug>
#include <qwt_plot_renderer.h>
#include "mesurement.h"
#include "panel.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;

    pBase = scanbase::instanse();

    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();
//    QVBoxLayout *layoutTopLeft       = new QVBoxLayout();
//    QGridLayout *layoutTopLeftDown   = new QGridLayout();

//    QSpacerItem *vs2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    columnPercent<<20<<20<<20<<20<<20;
    lst<<"Lens Name"<<"AConst"<<"ACD"<<"SF"<<"FORMULA";
    twLens = new adjview(3, lst, columnPercent);
    twLens->setMinimumWidth(400);
//    twLens->setMaximumWidth(300);
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
//    QString str = "SELECT  name, mfg, aconst, acd from lens;";
    QString str = QString("SELECT lens.name as 'Lens Name',lens.aconst,lens.acd,lens.sf,doctor_lens.nom_formula FROM patient, doctor_lens, lens ON patient.doctor=doctor_lens.id_doctor AND lens.id=doctor_lens.id_lens WHERE 0=1;");
    modelMainLens->setQuery(str);
    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
    modelMainLens->setHeaderData(1, Qt::Horizontal, "AConst", Qt::DisplayRole);
    modelMainLens->setHeaderData(2, Qt::Horizontal, "ACD", Qt::DisplayRole);
    modelMainLens->setHeaderData(3, Qt::Horizontal, "SF", Qt::DisplayRole);
    modelMainLens->setHeaderData(4, Qt::Horizontal, "FORMULA", Qt::DisplayRole);


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
//        model->item   (i, 2)->setFont(font);
        model->item   (i, 2)->setEditable(false);
        model->item   (i, 2)->setEnabled(false);

    }
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    twK->setPalette(palette);
//----------------------------------

    pCalcPatient = new calculator_patient();

//-----------------------------------
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
    //--------------------------------

    twRx = new adjview(1, 2, columnPercent);
    model = (QStandardItemModel*)twRx->model();
    model->setItem(0, 0, new QStandardItem(baseMapA[3]));
    model->item   (0, 0)->setBackground(Qt::lightGray);
    model->item   (0, 0)->setEditable(false);

    pbPrint = new QPushButton("Print");
//    pbPersCalc = new QPushButton("Personalized Calculation");


//    layoutTop->addWidget(pCalcPatient,  0, 0, 2, 1, Qt::AlignTop);

//    layoutTopLeftDown->addWidget(twK,  0, 0, 2, 1, Qt::AlignTop);
//    layoutTopLeftDown->addWidget(twA,  0, 1, 1, 1, Qt::AlignTop);
//    layoutTopLeftDown->addWidget(twRx, 1, 1);
//    layoutTopLeftDown->addWidget(pbOD,       2, 0, 2, 1, Qt::AlignTop);
//    layoutTopLeftDown->addWidget(pbPersCalc, 2, 1, 1, 1, Qt::AlignTop);

//    layoutTopLeft->addWidget(twName);
//    layoutTopLeft->addLayout(layoutTopLeftDown);
//    layoutTop->addLayout(layoutTopLeft);
//    layoutTop->addWidget(twLens, 0, Qt::AlignTop);
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
//     layout->addItem(vs2);
     layout->addWidget(pbPrint);

//     connect(pbOD, SIGNAL(clicked()), SLOT(changeEye()));
     connect(twK->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),  SLOT(setAL(QModelIndex,QModelIndex)));
     connect(pCalcPatient, SIGNAL(refreshFormula()), SLOT(refreshFormuls()));
     connect(pbPrint, SIGNAL(clicked()), SLOT(printPreview()));
}

//void calculator::refreshPatientParam(quint16 id)
//{
//    QStandardItemModel *model;
//    model = (QStandardItemModel*)twK->model();

//    QString str = QString("SELECT k1left, k2left, kleft, k1right, k2right, kright FROM patient WHERE id=%1;")
//            .arg(id);
//    QSqlQuery sql(str);
//    if(sql.exec())
//    {
//        sql.next();
//        if(pbOD->text()=="OD")
//        {
//            model->setData(model->index(1,1), sql.value(0).toDouble(), Qt::DisplayRole);
//            model->setData(model->index(2,1), sql.value(1).toDouble(), Qt::DisplayRole);
//            model->setData(model->index(3,1), sql.value(2).toDouble(), Qt::DisplayRole);
//        }
//        else
//        {
//            model->setData(model->index(1,1), sql.value(3).toDouble(), Qt::DisplayRole);
//            model->setData(model->index(2,1), sql.value(4).toDouble(), Qt::DisplayRole);
//            model->setData(model->index(3,1), sql.value(5).toDouble(), Qt::DisplayRole);
//        }
//    }
//}

void calculator::changeRow(quint8 numBase, quint16 id, QString Patient, QString Doctor)
{
    pCalcPatient->setPatient(id, Patient, Doctor);
    pCalcPatient->refreshPatientParam();
    refreshFormuls();
}

//void calculator::changeEye()
//{
//   pbOD->setText(pbOD->text()=="OD"?"OS":"OD");
//    Calculator(0, 12, 1, 2, 0, &stFormula);
//    Formula1->saveParam(&stFormula);
//}

void calculator::refreshFormuls()
{
    QList<int> columnPercent;
    stPatientParam patientParam;
    stPersonalParam personalParam;

    patientParam = pCalcPatient->getParam();
    personalParam = pCalcPatient->getPersonalParam();

    if(!((patientParam.ACD>0)&&(patientParam.AL>0)&&(patientParam.K>0)))
        return;

    columnPercent.clear();
    columnPercent<<20<<16<<22<<16<<14<<1<<11;
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
    QString str = QString("SELECT lens.name AS 'Lens Name',lens.aconst,lens.acd, lens.sf, formula.id, formula.name FROM patient, doctor_lens, lens, formula ON patient.doctor=doctor_lens.id_doctor AND lens.id=doctor_lens.id_lens AND doctor_lens.nom_formula=formula.id WHERE patient.id=%1;").arg(patientParam.id);
    modelMainLens->setQuery(str);

    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
    modelMainLens->setHeaderData(1, Qt::Horizontal, "AConst", Qt::DisplayRole);
    modelMainLens->setHeaderData(2, Qt::Horizontal, "ACD", Qt::DisplayRole);
    modelMainLens->setHeaderData(3, Qt::Horizontal, "SF", Qt::DisplayRole);
    modelMainLens->setHeaderData(4, Qt::Horizontal, "NUM", Qt::DisplayRole);
    modelMainLens->setHeaderData(5, Qt::Horizontal, "FORMULA", Qt::DisplayRole);

    twLens->setColumnHidden(4, true);

    Formula1->setEnabled(false);
    Formula2->setEnabled(false);
    Formula3->setEnabled(false);

    for(quint8 i=0; i<modelMainLens->rowCount() && i<3; i++)
    {
        quint8 nFormula;
        QString lensName, lensAconst, lensAcd, lensFs;
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
            Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, patientParam.K, patientParam.AL, patientParam.ACD);
            Formula1->setEnabled(true);
            break;
        case 1:
            Formula2->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, patientParam.K, patientParam.AL, patientParam.ACD);
            Formula2->setEnabled(true);
            break;
        case 2:
            Formula3->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, patientParam.K, patientParam.AL, patientParam.ACD);
            Formula3->setEnabled(true);
        default:
            break;
        }
    }
}

void calculator::refreshAl(double AL)
{
//    QStandardItemModel *model;
//    model = (QStandardItemModel*)twK->model();
//    model->setData(model->index(0,1), AL, Qt::DisplayRole);
//    pCalcPatient->ref
}


void calculator::refreshMeasure(stMeasureParam measureParam)
{
pCalcPatient->refreshMeasure(measureParam);
}


void calculator::refreshAcd(double Acd)
{
    ACD_measure = Acd;
    QStandardItemModel *model;
    model = (QStandardItemModel*)twK->model();
    model->setData(model->index(4,1), Acd, Qt::DisplayRole);
}

void calculator::setAL(QModelIndex val1, QModelIndex val2)
{
    double dTmp;
    if(val1.column()==1)
    {
        if ((val1.row()==0) || (val1.row()==3) || (val1.row()==4))
            refreshFormuls();
        else
        {
            QStandardItemModel *model;
            model = (QStandardItemModel*)twK->model();
            dTmp =  twK->model()->itemData(twK->model()->index(1,1)).value(0).toDouble();
            dTmp += twK->model()->itemData(twK->model()->index(2,1)).value(0).toDouble();
            dTmp /= 2;
            model->setData(model->index(3, 1), dTmp, Qt::DisplayRole);
        }
    }
}

void calculator::printPreview()
{
    QPrinter             printer( QPrinter::HighResolution );
    QPrintPreviewDialog  preview( &printer, this );
    connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
    preview.exec();
}

void calculator::print( QPrinter* printer )
{
    stPrintSample printSample;
    double x[2048], y[2048];
    quint16 kolvo;
    QObject * parentClass = parent()->parent();  //get parent for current class
    Panel * pClass = qobject_cast<Panel *>(parentClass); //cast QObject * to ParentClass
    if(pClass == NULL)
       return;

  // create painter for drawing print page
  QPainter painter( printer );
  int      w = printer->pageRect().width();
  int      h = printer->pageRect().height();
  QRect    page( 0, 0, w, h );
  // create a font appropriate to page size
  QFont    font = painter.font();
  font.setPixelSize( (w+h) / 100 );
  painter.setFont( font );
  // draw labels in corners of page
  painter.drawText( page, Qt::AlignTop    | Qt::AlignLeft, "QSimulate" );
//  painter.drawText( page, Qt::AlignBottom | Qt::AlignLeft, QString(getenv("USER")) );
//  painter.drawText( page, Qt::AlignBottom | Qt::AlignRight,
//                    QDateTime::currentDateTime().toString( Qt::DefaultLocaleShortDate ) );

//  QPixmap pixmap(Formula1->size());
//  Formula1->render(&pixmap);

  printSample = pClass->Mesur->pSampleTable->printSample();


  QwtPlotRenderer renderer;
  pPlotPrint1 = new Plot(this, true);
  kolvo = 0;
  foreach (quint8 val, printSample.sample1)
  {
      x[kolvo] = kolvo;
      y[kolvo] = double(val);
      kolvo++;
  }
  pPlotPrint1->drawSample(x, y, 1024);
  pPlotPrint1->enableAxis(QwtPlot::xTop,false);
  pPlotPrint1->enableAxis(QwtPlot::xBottom,false);
  pPlotPrint1->enableAxis(QwtPlot::yLeft,false);
  pPlotPrint1->replot();
  renderer.render(pPlotPrint1, &painter, QRectF(500,1000,2000,1800));

  pPlotPrint2 = new Plot(this, true);
  kolvo = 0;
  foreach (quint8 val, printSample.sample2)
  {
      x[kolvo] = kolvo;
      y[kolvo] = double(val);
      kolvo++;
  }
  pPlotPrint2->drawSample(x, y, 1024);
  pPlotPrint2->enableAxis(QwtPlot::xTop,false);
  pPlotPrint2->enableAxis(QwtPlot::xBottom,false);
  pPlotPrint2->enableAxis(QwtPlot::yLeft,false);
  pPlotPrint2->replot();
  renderer.render(pPlotPrint2, &painter, QRectF(2700,1000,2000,1800));

  pPlotPrint3 = new Plot(this, true);
  kolvo = 0;
  foreach (quint8 val, printSample.sample3)
  {
      x[kolvo] = kolvo;
      y[kolvo] = double(val);
      kolvo++;
  }
  pPlotPrint3->drawSample(x, y, 1024);
  pPlotPrint3->enableAxis(QwtPlot::xTop,false);
  pPlotPrint3->enableAxis(QwtPlot::xBottom,false);
  pPlotPrint3->enableAxis(QwtPlot::yLeft,false);
  pPlotPrint3->replot();
  renderer.render(pPlotPrint3, &painter, QRectF(500,3600,2000,1800));

//  painter.drawPixmap(500,500,pixmap.height(),pixmap.width(),pixmap);
  painter.drawRect(500, 200, 4000, 300);

  page.adjust( w/20, h/20, -w/20, -h/20 );

}



