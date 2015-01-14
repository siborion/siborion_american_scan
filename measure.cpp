#include "measure.h"

Measure::Measure(QWidget *parent, CurParam *link) :
    QWidget(parent)
{
    curParam = link;

    QGridLayout *layout     = new QGridLayout(this);
    layout->setVerticalSpacing(2);

    pBigViewCur = new Bigviewnumcur(this, curParam);
    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this, false, curParam);
    glPlot->addWidget(pBigViewCur, 0, 0);
    glPlot->addWidget(pPlot,       1, 0);

    pKey = new key_radio(this, curParam);
    pSampleTable = new sampletable(this, curParam);
    velosity = new Velosity();
    pBigView = new bigviewnum(this, curParam);

    layout->addWidget(fmPlot      ,0,0,3,1);
    layout->addWidget(pKey        ,3,0,1,2);
    layout->addWidget(pSampleTable,0,1);
    layout->addWidget(velosity    ,1,1);
    layout->addWidget(pBigView    ,2,1);

    connect(velosity,SIGNAL(doScan(bool*)),SLOT(doScanSlot(bool*)));
    connect(velosity,SIGNAL(doStop()),SLOT(stopMeasureSlot()));

    connect(pSampleTable,SIGNAL(changeRow(stMeasureParam*)),pPlot,SLOT(updateSample(stMeasureParam*)));
    connect(pSampleTable,SIGNAL(changeRow(stMeasureParam*)),pBigViewCur,SLOT(setDisplay(stMeasureParam*)));
    connect(pSampleTable,SIGNAL(sendAvg(stAverageParam*)),pBigView,SLOT(setDisplay(stAverageParam*)));
    connect(pSampleTable,SIGNAL(stopMeasure()),SLOT(stopMeasureSlot()));
    connect(pPlot,SIGNAL(refreshTable(stMeasureParam*)),SLOT(refreshTableSlot(stMeasureParam*)));
    connect(pKey,SIGNAL(changeInterval()),pSampleTable,SLOT(changeRegimManual()));
    connect(pKey,SIGNAL(changeInterval()),pPlot,SLOT(updateInterval()));
    connect(pKey,SIGNAL(changeInterval()),pBigViewCur,SLOT(setRegim()));
    connect(pKey,SIGNAL(changeInterval()),pBigView,SLOT(setRegim()));
    connect(pKey,SIGNAL(changeInterval()),SLOT(changeGlasSlot()));

    connect(pSampleTable,SIGNAL(changeGlas()),SLOT(changeGlasSlot()));;
    connect(pSampleTable,SIGNAL(changeGlas()),pKey,SLOT(refresh()));
    connect(pSampleTable,SIGNAL(changeGlas()),pBigViewCur,SLOT(setRegim()));


    connect(pSampleTable,SIGNAL(save(QStandardItemModel*,QStandardItemModel*)),SLOT(saveSlot(QStandardItemModel*,QStandardItemModel*)));

}

void Measure::saveSlot(QStandardItemModel *OD, QStandardItemModel *OS)
{
    emit save(OD, OS);
}

void Measure::changeGlasSlot()
{
    emit changeGlas();
}

void Measure::doScanSlot(bool *doMeasure)
{
    SampleManual.clear();
    emit doScan(doMeasure);
    if(*doMeasure)
        pSampleTable->startMeasure();
}

void Measure::resiveData(QByteArray *Sample)
{
    pPlot->drawSample(Sample);
}

void Measure::addSample(QByteArray *Sample, QList<quint16> *extremum, stMeasureParam *measureParam)
{
    if(curParam->regimMeasure != REGIM::MANUAL)
    {
        pSampleTable->addSample(Sample, extremum, measureParam);
        pBigViewCur->setDisplay(measureParam);
    }
    else
    {
        //Сохраняем последнюю удачнуювыборку
        SampleManual   = *Sample;
        extremumManual = *extremum;
        measureParamManual = *measureParam;
        if(curTime.addMSecs(500)<QTime::currentTime())
        {
            curTime = QTime::currentTime();
            pBigViewCur->setDisplay(measureParam);
        }
    }
}

void Measure::refreshTableSlot(stMeasureParam *measureParam)
{
    emit refreshTable(measureParam);
    pSampleTable->editSample(measureParam);
    pBigViewCur->setDisplay(measureParam);
}

void Measure::stopMeasureSlot()
{
    if(curParam->regimMeasure == REGIM::MANUAL)
    {
        if(SampleManual.length()>0)
        {
            pSampleTable->addSample(&SampleManual, &extremumManual, &measureParamManual);
            pBigViewCur->setDisplay(&measureParamManual);
        }
    }
    emit stopMeasure();
}

void Measure::updatePatient()
{
    pBigViewCur->updatePatient();
    pSampleTable->clearAll();
    pBigView->clearAll();
    pPlot->clearAll();
}
