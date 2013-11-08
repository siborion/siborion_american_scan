#include "qapplication.h"
#include "mainwindow.h"

int main ( int argc, char **argv )
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a( argc, argv );
    MainWindow w;
    w.resize( 540, 400 );
    w.show();
    return a.exec();
}
