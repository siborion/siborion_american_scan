#include "qapplication.h"
#include "mainwindow.h"
#include <qt_windows.h>
#include "ftd2xx.h"

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



FT_STATUS ftStatus = FT_ListDevices(0, 0, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
        if (ftStatus!=FT_OK) //Get first device serial number
        {
                printf("Couldn't get FTDI device name");
        }
 
        FT_HANDLE ftHandle = FT_W32_CreateFile(0,
                GENERIC_READ|GENERIC_WRITE,
                0,
                0,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | 	FT_OPEN_BY_SERIAL_NUMBER,
                0); //



//    w.resize( 900, 400 );
//    w.show();
    w.showMaximized();
    return a.exec();
}
