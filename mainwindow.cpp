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

    bases->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
