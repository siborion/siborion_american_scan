#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "control.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scanbase = new Scanbase(parent);

    bases = new Bases(parent);
    measure = new Measure(parent);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(bases, "Data Bases");
    ui->tabWidget->addTab(measure, "Measurement");

    connect(bases,SIGNAL(getModel(Base::TypeBase,QSqlQueryModel**)),scanbase,SLOT(getBasesModel(Base::TypeBase,QSqlQueryModel**)));

    connect(bases,SIGNAL(updateCurPatient(quint16)),scanbase,SLOT(updateCurPatient(quint16)));
    connect(scanbase,SIGNAL(setStPatient(QMap<QString,QString>*)),bases,SLOT(setStPatient(QMap<QString,QString>*)));
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



    bases->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
