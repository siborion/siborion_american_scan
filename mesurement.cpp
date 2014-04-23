#include "mesurement.h"

mesurement::mesurement(QWidget *parent) :
    QWidget(parent)
{
    pBase = scanbase::instanse();

    QList<int> columnPercent;
    QStringList lst;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QVBoxLayout *layoutRight = new QVBoxLayout();
    QGridLayout *layoutBot = new QGridLayout();

    pBigView = new bigviewnum();
    pBigView->setMinimumHeight(100);
    pBigView->setMaximumHeight(150);

    pBigViewCur = new bigviewnumcur();
    pBigViewCur->setMinimumHeight(50);
    pBigViewCur->setMaximumHeight(50);
//    pBigViewCur->setMinimumWidth(250);
//    pBigViewCur->setMaximumWidth(250);


//------------------------------------ TableView
    QFrame *fmPatient = new QFrame();
    QFrame *fmLens = new QFrame();
    QFrame *fmVelocity = new QFrame();
    fmPatient->setFrameShape(QFrame::WinPanel);
    fmPatient->setFrameShadow(QFrame::Raised);
    fmLens->setFrameShape(QFrame::WinPanel);
    fmLens->setFrameShadow(QFrame::Raised);
    fmVelocity->setFrameShape(QFrame::WinPanel);
    fmVelocity->setFrameShadow(QFrame::Raised);
    fmPatient->setMaximumHeight(100);
    fmLens->setMaximumHeight(100);
    fmVelocity->setMaximumHeight(100);

    QGridLayout *twPatient  = new QGridLayout(fmPatient);
    QGridLayout *twLens     = new QGridLayout(fmLens);
    QGridLayout *twVelocity = new QGridLayout(fmVelocity);
    twPatient->setSpacing(2); twLens->setSpacing(2); twVelocity->setSpacing(2);

//    layoutTop->addWidget(fmPatient);
//    layoutTop->addWidget(fmLens);
//    layoutTop->addWidget(fmVelocity);

//--------------------*twPatient---------------------------------------
    QLabel *patientName = new QLabel("Patient Name:");
    QLabel *measureData = new QLabel("Data:");
    QLabel *doctorName  = new QLabel("Doctor Name:");
    QComboBox *VALname = new QComboBox();
    QLineEdit *VALdata = new QLineEdit();
    QComboBox *VALdoctor = new QComboBox();
    VALdata->setText(QString("%1").arg(QDate::currentDate().toString("yyyy.MM.dd")));


    modelName = new QSqlTableModel ();
    modelName->setTable("v_cbpatient");
    modelName->select();
    VALname->setModel(modelName);
    VALname->setModelColumn(modelName->fieldIndex("name"));

    modelDoctor = new QSqlTableModel ();
    modelDoctor->setTable("v_cbdoctor");
    modelDoctor->select();
    VALdoctor->setModel(modelDoctor);
    VALdoctor->setModelColumn(modelDoctor->fieldIndex("name"));

    twPatient->addWidget(patientName);
    twPatient->addWidget(measureData);
    twPatient->addWidget(doctorName);
    twPatient->addWidget(VALname,0,1);
    twPatient->addWidget(VALdata,1,1);
    twPatient->addWidget(VALdoctor,2,1);
//--------------------*twLens--------------------------------------------
    QLabel *axialLenght = new QLabel("Axial Lenght As: ACD+LT+VIT");
    QLabel *acd  = new QLabel("ACD @ 1532 m/sec:");
    QLabel *lt   = new QLabel("LT @ 1641 m/sec:");
    QLabel *vit  = new QLabel("VIT @ 1641 m/sec:");
    QLabel *mm0  = new QLabel("mm");
    QLabel *mm1  = new QLabel("mm");
    QLabel *mm2  = new QLabel("mm");
    QLabel *mm3  = new QLabel("mm");
    VALaxial = new QLineEdit();
    VALacd = new QLineEdit();
    VALlt = new QLineEdit();
    VALvit = new QLineEdit();

    twLens->addWidget(axialLenght);
    twLens->addWidget(acd);
    twLens->addWidget(lt);
    twLens->addWidget(vit);
    twLens->addWidget(VALaxial, 0, 1);
    twLens->addWidget(VALacd, 1, 1);
    twLens->addWidget(VALlt, 2, 1);
    twLens->addWidget(VALvit, 3, 1);
    twLens->addWidget(mm0, 0, 2);
    twLens->addWidget(mm1, 1, 2);
    twLens->addWidget(mm2, 2, 2);
    twLens->addWidget(mm3, 3, 2);
//--------------------*twVelocity--------------------------------------------
    QLabel *al = new QLabel("AL @ Ave.Velocity 1550 m/sec");
    average  = new QLabel("Average");
    QLabel *sd   = new QLabel("SD");
    VALal = new QLineEdit();
    VALaverage = new QLineEdit();
    VALsd = new QLineEdit();

    twVelocity->addWidget(al);
    twVelocity->addWidget(average);
    twVelocity->addWidget(sd);
    twVelocity->addWidget(VALal, 0, 1);
    twVelocity->addWidget(VALaverage, 1, 1);
    twVelocity->addWidget(VALsd, 2, 1);

    QFrame *fmPlot = new QFrame();
    fmPlot->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 100);"));
    fmPlot->setFrameShape(QFrame::NoFrame);
    fmPlot->setFrameShadow(QFrame::Plain);
//    QSpacerItem *vs = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout *glPlot  = new QGridLayout(fmPlot);
    pPlot = new Plot(this);

//    QVBoxLayout *layoutBigView = new QVBoxLayout(this);
//    layoutBigView->addItem(vs);
//    layoutBigView->addWidget(pBigViewCur);
    glPlot->addWidget(pBigViewCur);
//    glPlot->addLayout(layoutBigView,0,0);
    glPlot->addWidget(pPlot,1,0);

    lst.clear();
    columnPercent.clear();
    columnPercent<<10      <<30            <<15      <<15       <<15      <<15;
    lst          <<tr("No")<<tr("AveVelAl")<<tr("AL")<<tr("ACD")<<tr("LT")<<tr("VIT");
    twMeas  = new adjview(10, lst, columnPercent);
    twMeas->setSelectionBehavior(QAbstractItemView::SelectRows);
    twMeas->setMinimumWidth(250);

    pSampleTable = new sampletable();

    QPushButton *pbOd = new QPushButton(tr("Change Eye"));
//    QFont font;
//    font.setPointSize(24);
//    font.setBold(true);
//    font.setWeight(75);
//    pbOd->setFont(font);
//    pbOd->setFont(font);

    pKey = new key_radio();

    layoutBot->addWidget(fmPlot, 0, 0);
    layoutBot->addWidget(pKey,1,0);
    layoutBot->addLayout(layoutRight, 0, 1, 2, 1);

    QPushButton *pbDel = new QPushButton(tr("Delete"));

    layoutRight->addWidget(pBigView);
    layoutRight->addWidget(pbOd);
//    layoutRight->addWidget(twMeas);
    layoutRight->addWidget(pSampleTable);
    layoutRight->addWidget(pbDel);

    layout->addLayout(layoutTop, 0);
    layout->addLayout(layoutBot, 5);



    pBaseFill = new basefill(0, children(), (QString)"history");

    connect(pKey, SIGNAL(keyAuto()), pSampleTable, SLOT(getFileSample()));
//    connect(twMeas, SIGNAL(clicked(QModelIndex)), SLOT(changeRow(QModelIndex)));
    connect(pPlot, SIGNAL(refreshTable(stMainParam)), pSampleTable, SLOT(refreshTable(stMainParam)));
//    connect(pKey, SIGNAL(keySave()), SLOT(save()));
    connect(pSampleTable, SIGNAL(changeRow(QList<quint16>)), SLOT(changeRow(QList<quint16> )));
    connect(pSampleTable, SIGNAL(refreshMainParam()), SLOT(refreshMainParam()));
    connect(pbDel, SIGNAL(clicked()), pSampleTable, SLOT(delSample()));
    connect(pbOd, SIGNAL(pressed()), SLOT(changeEye()));
}

void mesurement::changeRow(QList<quint16> extremum)
{
    double x[1024], y[1024];
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
    VALaxial->setText(QString("%1").arg(pSampleTable->resultParam.AL));
    VALacd->setText(QString("%1").arg(pSampleTable->resultParam.ACD));
    VALlt->setText(QString("%1").arg(pSampleTable->resultParam.LT));
    VALvit->setText(QString("%1").arg(pSampleTable->resultParam.Vit));
    pBigView->setDisplay(pSampleTable->resultParam.sumAl, pSampleTable->resultParam.AvgAcd, pSampleTable->resultParam.AvgLt, pSampleTable->resultParam.AvgVit, pSampleTable->resultParam.devAl);
    pBigViewCur->setDisplay(pSampleTable->resultParam.AL, pSampleTable->resultParam.ACD, pSampleTable->resultParam.LT, pSampleTable->resultParam.Vit);

    average->setText(QString("Average (count %1)").arg(pSampleTable->resultParam.countSample));
    VALaverage->setText(QString("%1").arg(pSampleTable->resultParam.sumAl));
    VALsd->setText(QString("%1").arg(pSampleTable->resultParam.SD));
}

void mesurement::changeRow(quint8 idType, quint16 idRow, QString Text)
{
    pBigViewCur->setDisplay(Text);
}

void mesurement::changeEye()
{
    pBigViewCur->changeEye();
}
