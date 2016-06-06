#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QStyle>
#include "qtrpt.h"


//#include "control.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curParam = new CurParam(this);
    scanbase = new Scanbase(this, curParam);
    pCalculator = new calculator(this, curParam);
    bases = new Bases(this);
    measure = new Measure(this, curParam);
    device = new Device(this);
    parcer = new Parcer(this, curParam);
    bscan = new Bscan(this, curParam);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(bases, "Data Bases");
    ui->tabWidget->addTab(measure, "Measurement");
    ui->tabWidget->addTab(pCalculator, "Calculator");
    ui->tabWidget->addTab(bscan, "B-Scan");


    pCalculator->twMeas = measure->pSampleTable->twMeas;

    connect(bases,SIGNAL(getModel(Base::TypeBase,QSqlQueryModel**)),scanbase,SLOT(getBasesModel(Base::TypeBase,QSqlQueryModel**)));

    connect(bases,SIGNAL(updateCurPatient(quint16)),scanbase,SLOT(updateCurPatient(quint16)));
    connect(bases,SIGNAL(updateCurPatient(quint16)),pCalculator,SLOT(updatePatient()));
//    connect(bases,SIGNAL(updateCurPatient(quint16)), SLOT(updatePatient()));
    connect(measure,SIGNAL(changeGlas()),pCalculator,SLOT(updatePatient()));

    connect(pCalculator, SIGNAL(changeSideCalculator()), measure, SLOT(changeSideCalculatorSlot()));

    connect(measure,SIGNAL(stopMeasure()),pCalculator,SLOT(updatePatient()));


    connect(scanbase,SIGNAL(setStPatient(QMap<QString,QString>*)),SLOT(setStPatient(QMap<QString,QString>*)));


    connect(bases,SIGNAL(savePatient(quint16*)),scanbase,SLOT(saveCurPatient(quint16*)));
    connect(bases,SIGNAL(delPatient()),scanbase,SLOT(delPatient()));

    connect(bases,SIGNAL(updateCurDoctor(quint16)),scanbase,SLOT(updateCurDoctor(quint16)));
    connect(scanbase,SIGNAL(setStDoctor(QMap<QString,QString>*)),bases,SLOT(setStDoctor(QMap<QString,QString>*)));
    connect(bases,SIGNAL(saveDoctor(quint16*)),scanbase,SLOT(saveCurDoctor(quint16*)));
    connect(bases,SIGNAL(delDoctor()),scanbase,SLOT(delDoctor()));
    connect(bases,SIGNAL(saveDocLens(quint16,QMap<quint16,quint16>*)),scanbase,SLOT(saveDocLens(quint16,QMap<quint16,quint16>*)));

    connect(bases,SIGNAL(updateCurLens(quint16)),scanbase,SLOT(updateCurLens(quint16)));
    connect(scanbase,SIGNAL(setStLens(QMap<QString,QString>*)),bases,SLOT(setStLens(QMap<QString,QString>*)));
    connect(bases,SIGNAL(saveLens(quint16*)),scanbase,SLOT(saveCurLens(quint16*)));
    connect(bases,SIGNAL(delLens()),scanbase,SLOT(delLens()));

    connect(measure,SIGNAL(doScan(bool*)),device,SLOT(openDevice(bool*)));
    connect(measure,SIGNAL(refreshTable(stMeasureParam*)),parcer,SLOT(calculateParam(stMeasureParam*)));
    connect(device,SIGNAL(resiveData(QByteArray*)),SLOT(resiveDataSlot(QByteArray*)));

    connect(measure,SIGNAL(stopMeasure()),device,SLOT(stopMeasure()));

    connect(scanbase,SIGNAL(setLens(QSqlQueryModel*)),pCalculator,SLOT(refreshLens(QSqlQueryModel*)));

    connect(measure,SIGNAL(save(QStandardItemModel*,QStandardItemModel*)),scanbase,SLOT(saveSlot(QStandardItemModel*,QStandardItemModel*)));

    bases->Init();
    moveWindowToCenter();

}

void MainWindow::moveWindowToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(0,0);
}

void MainWindow::resiveDataSlot(QByteArray *Sample)
{
    stMeasureParam measureParam;
    QList<quint16> exstremum;
    measure->resiveData(Sample);
    if(parcer->findExtremum(Sample, &exstremum, &measureParam))
    {
        measure->addSample(Sample, &exstremum, &measureParam);
    }
}

void MainWindow::setStPatient(QMap <QString, QString> *stPatientBases)
{
    QString str;
    bases->setStPatient(stPatientBases);
    measure->updatePatient();
    bscan->updatePatient();
    if(curParam->doctorName.isEmpty())
        str.append("Ocusvm");
    else
        str.append(QString("Ocusvm / %1 / %2").arg(curParam->patientName).arg(curParam->doctorName));
    this->setWindowTitle(str);
    qDebug()<<str;
}

MainWindow::~MainWindow()
{
    delete ui;
}
