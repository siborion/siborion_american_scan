#include <QApplication>
#include "mainwindow.h"
//#include <QSound>
#include <QStyleFactory>
#include <QInputDialog>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);


    qDebug()<<QStyleFactory::keys();

    bool ok;
//    QString text = QInputDialog::getText(0, ("QInputDialog::getText()"),
//                                         ("User name:"), QLineEdit::Normal,
//                                         QDir::home().dirName(), &ok);


    QString textStyle = QInputDialog::getItem(0, ("Style"),
                          ("Style:"),
                          QStyleFactory::keys(), 0, true, &ok);


    a.setStyle(QStyleFactory::create(textStyle));
    //    a.setStyle(QStyleFactory::create("Fusion"));
    //a.setStyle(QStyleFactory::create("windows"));
    //        a.setStyle(QStyleFactory::create("WindowsXP"));
    //a.setStyle(QStyleFactory::create("plastique"));
     //a.setStyle(QStyleFactory::create("WindowsVista"));


    a.addLibraryPath(a.applicationDirPath()+"/plugins");
    MainWindow w;
    QApplication::beep();
    printf("\a");
    //    QSound bells(":/test/sinus");
    //    bells.setLoops(10);
    //    bells.play();
    //w.show();
    w.showMaximized();
    return a.exec();
}
