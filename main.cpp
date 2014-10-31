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


FT_STATUS ftStatus;
DWORD ftNumDevice;
FT_DEVICE_LIST_INFO_NODE *devInfo;
ftStatus = FT_CreateDeviceInfoList (&ftNumDevice);
if (ftStatus==FT_OK)
{
    if(ftNumDevice>0)
    {
        devInfo =(FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*ftNumDevice);
        //Получить информацию о каждом устройстве в массиве
        ftStatus = FT_GetDeviceInfoList(devInfo,&ftNumDevice);
        if (ftStatus == FT_OK) {
            //Если успешно
            for (int i = 0; i < ftNumDevice; i++) {
                printf("Dev %d:\n",i);                                  //Напечатать номер устройства, начиная с 0
                printf("  Flags=0x%x\n",devInfo[i].Flags);              //Напечатать все поля каждой структуры
                printf("  Type=0x%x\n",devInfo[i].Type);
                printf("  ID=0x%x\n",devInfo[i].ID);
                printf("  LocId=0x%x\n",devInfo[i].LocId);
                printf("  SerialNumber=%s\n",devInfo[i].SerialNumber);
                printf("  Description=%s\n",devInfo[i].Description);
                printf("  ftHandle=0x%x\n",devInfo[i].ftHandle);
            }
        }
    }
}

//qDebug()<<hhh;
//qDebug()<<ttt;


//FT_STATUS ftStatus = FT_ListDevices(0, 0, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
//        if (ftStatus!=FT_OK) //Get first device serial number
//        {
//                printf("Couldn't get FTDI device name");
//        }
 
//        FT_HANDLE ftHandle = FT_W32_CreateFile(0,
//                GENERIC_READ|GENERIC_WRITE,
//                0,
//                0,
//                OPEN_EXISTING,
//                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | 	FT_OPEN_BY_SERIAL_NUMBER,
//                0); //



//    w.resize( 900, 400 );
//    w.show();
    w.showMaximized();
    return a.exec();
}
