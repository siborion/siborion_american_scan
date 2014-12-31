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

//    bases->stPatient = &scanbase->curPatient;

    connect(bases,SIGNAL(getModel(Base::TypeBase,QSqlQueryModel**)),scanbase,SLOT(getBasesModel(Base::TypeBase,QSqlQueryModel**)));
//    connect(scanbase,SIGNAL(setBasesModel(QSqlQueryModel*)),bases,SLOT(setModel(QSqlQueryModel*)));

    connect(bases,SIGNAL(updateCurPatient(quint16)),scanbase,SLOT(updateCurPatient(quint16)));
    connect(scanbase,SIGNAL(setStPatient(StPatient*)),bases,SLOT(setStPatient(StPatient*)));

    bases->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
