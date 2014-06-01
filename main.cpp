#include "qapplication.h"
#include "mainwindow.h"

int main ( int argc, char **argv )
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
//    paths.append("imageformats");
    paths.append("platforms");
//    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a( argc, argv );
    a.addLibraryPath(a.applicationDirPath()+"/plugins");
    MainWindow w;
    w.resize( 900, 400 );
    w.show();
    return a.exec();
}
