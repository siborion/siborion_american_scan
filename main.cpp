#include "qapplication.h"
#include "mainwindow.h"

int main ( int argc, char **argv )
{

//    Q_INIT_RESOURCE(resources);
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a( argc, argv );
//    a.addLibraryPath("D:/_SVN/SibOrion/AmericanOptic/scan1/release/plugins/");
//    a->addLibraryPath("/plugins/");
    MainWindow w;
    w.resize( 540, 400 );
    w.show();
    return a.exec();
}
