#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    a.addLibraryPath(a.applicationDirPath()+"/plugins");
    MainWindow w;
    //w.show();
    w.showMaximized();
    return a.exec();
}
