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

    connect(bases,SIGNAL(getModel(Base::TypeBase)),scanbase,SLOT(getBasesModel(Base::TypeBase)));
    connect(scanbase, SIGNAL(setBasesModel(QSqlQueryModel*)),bases,SLOT(setModel(QSqlQueryModel*)));

    bases->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
