#include <QApplication>
#include "mainwindow.h"
#include <QSound>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    a.addLibraryPath(a.applicationDirPath()+"/plugins");
    MainWindow w;
//    QApplication::beep();
//    QSound bells(":/test/sinus");
//    bells.setLoops(10);
//    bells.play();
    //w.show();
    w.showMaximized();
    return a.exec();
}
