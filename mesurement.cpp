#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();

    QList<int> columnPercent;
    QStringList lst;

//    QVBoxLayout *layoutRight = new QVBoxLayout();
    QGridLayout *layoutBot = new QGridLayout(this);

    pBigView = new bigviewnum();
    pBigView->setMinimumHeight(120);
    pBigView->setMaximumHeight(150);

    pBigViewCur = new bigviewnumcur();
    pBigViewCur->setMinimumHeight(50);
    pBigViewCur->setMaximumHeight(50);

    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 100);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this);

    glPlot->addWidget(pBigViewCur);
    glPlot->addWidget(pPlot,1,0);

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
    twMeas->setMinimumWidth(250);

    pSampleTable = new sampletable();

    QSpacerItem *vs = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    pKey = new key_radio();
    QPushButton *pbDel = new QPushButton(tr("Delete"));


    layoutBot->addWidget(fmPlot, 0, 0, 4, 1);
    layoutBot->addWidget(pKey,5,0,1,1);

    layoutBot->addWidget(pSampleTable,0,1);
    layoutBot->addWidget(pbDel,1,1);
    layoutBot->addItem(vs,2,1);
    layoutBot->addWidget(pBigView,3,1);


//    layoutRight->addWidget(pbOd);

//    pBaseFill = new basefill(0, children(), (QString)"history");

    connect(pKey, SIGNAL(keyAuto()), pSampleTable, SLOT(getFileSample()));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), pSampleTable, SLOT(refreshTable(stMainParam)));
    connect(pSampleTable, SIGNAL(changeRow(QList<quint16>)), SLOT(changeRow(QList<quint16> )));
    connect(pSampleTable, SIGNAL(refreshMainParam()), SLOT(refreshMainParam()));
    connect(pbDel, SIGNAL(clicked()), pSampleTable, SLOT(delSample()));
//    connect(pbOd, SIGNAL(pressed()), SLOT(changeEye()));
}

void mesurement::changeRow(QList<quint16> extremum)
{
    double x[2024], y[2024];
    quint16 kolvo = 0;

    foreach (quint8 val, pSampleTable->baSample)
    {
        x[kolvo] = kolvo;
        y[kolvo] = double(val);
        kolvo++;
    }

    pPlot->drawSample(x, y, 1000);
    pPlot->allExtremum = extremum;
    pPlot->drawMarker(pSampleTable->mainParam.Start, "Start");
    pPlot->drawMarker((double)pSampleTable->mainParam.Start,(double)60, Qt::yellow);
    pPlot->drawMarker(pSampleTable->mainParam.L1, "L1");
    pPlot->drawMarker((double)pSampleTable->mainParam.L1,(double)60, Qt::yellow);
    pPlot->drawMarker(pSampleTable->mainParam.L2, "L2");
    pPlot->drawMarker((double)pSampleTable->mainParam.L2,(double)60, Qt::yellow);
    pPlot->drawMarker(pSampleTable->mainParam.Retina, "Retina");
    pPlot->drawMarker((double)pSampleTable->mainParam.Retina,(double)60, Qt::yellow);
}

void mesurement::refreshMainParam()
{
//    VALaxial->setText(QString("%1").arg(pSampleTable->resultParam.AL));
//    VALacd->setText(QString("%1").arg(pSampleTable->resultParam.ACD));
//    VALlt->setText(QString("%1").arg(pSampleTable->resultParam.LT));
//    VALvit->setText(QString("%1").arg(pSampleTable->resultParam.Vit));
    pBigView->setDisplay(pSampleTable->resultParam.AvgAl, pSampleTable->resultParam.AvgAcd, pSampleTable->resultParam.AvgLt, pSampleTable->resultParam.AvgVit, pSampleTable->resultParam.devAl, pSampleTable->resultParam.devAcd, pSampleTable->resultParam.devLt, pSampleTable->resultParam.devVit);
    pBigViewCur->setDisplay(pSampleTable->resultParam.AL, pSampleTable->resultParam.ACD, pSampleTable->resultParam.LT, pSampleTable->resultParam.Vit);

//    average->setText(QString("Average (count %1)").arg(pSampleTable->resultParam.countSample));
//    VALaverage->setText(QString("%1").arg(pSampleTable->resultParam.AvgAl));
//    VALsd->setText(QString("%1").arg(pSampleTable->resultParam.SD));
}

void mesurement::changeRow(quint8 idType, quint16 idRow, QString Text)
{
    switch(idType)
    {
    case BaseType::enPatient:
            pBigViewCur->setPatient(Text);
        break;
    case BaseType::enDoctor:
            pBigViewCur->setDoctor(Text);
        break;
    }
}

void mesurement::changeEye()
{
    pBigViewCur->changeEye();
}
