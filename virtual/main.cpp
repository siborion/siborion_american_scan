#include "qapplication.h"
#include "mainwindow.h"

int main ( int argc, char **argv )
{
    QApplication a( argc, argv );

//    QStringList paths = QCoreApplication::libraryPaths();
//    paths.append(".");
//    paths.append("platforms");
//    QCoreApplication::setLibraryPaths(paths);
//    a.addLibraryPath(a.applicationDirPath()+"/plugins");
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
