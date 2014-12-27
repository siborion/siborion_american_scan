#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "control.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Control control;

}

MainWindow::~MainWindow()
{
    delete ui;
}
