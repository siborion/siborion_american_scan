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
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(bases, "Data Bases");

    connect(bases,SIGNAL(getModel(Base::TypeBase,QSqlQueryModel**)),scanbase,SLOT(getBasesModel(Base::TypeBase,QSqlQueryModel**)));


    connect(bases,SIGNAL(updateCurPatient(quint16)),scanbase,SLOT(updateCurPatient(quint16)));
    connect(scanbase,SIGNAL(setStPatient(QMap<QString,QString>*)),bases,SLOT(setStPatient(QMap<QString,QString>*)));
    connect(bases,SIGNAL(savePatient(quint16*)),scanbase,SLOT(saveCurPatient(quint16*)));
    connect(bases,SIGNAL(delPatient()),scanbase,SLOT(delPatient()));

    connect(bases,SIGNAL(updateCurDoctor(quint16)),scanbase,SLOT(updateCurDoctor(quint16)));
    connect(scanbase,SIGNAL(setStDoctor(QMap<QString,QString>*)),bases,SLOT(setStDoctor(QMap<QString,QString>*)));
    connect(bases,SIGNAL(saveDoctor(quint16*)),scanbase,SLOT(saveCurDoctor(quint16*)));
    connect(bases,SIGNAL(delDoctor()),scanbase,SLOT(delDoctor()));


    bases->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
