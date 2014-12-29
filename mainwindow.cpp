#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "control.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bases = new Bases(parent);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(bases, "Data Bases");

    scanbase = new Scanbase(parent);


    connect(bases,SIGNAL(getBasesTable(QString)),scanbase,SLOT(getBasesTable(QString)));
    connect(scanbase, SIGNAL(setModel(QSqlQueryModel*)),bases,SLOT(setModel(QSqlQueryModel*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
