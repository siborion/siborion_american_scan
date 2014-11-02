#include "qapplication.h"
#include "mainwindow.h"
#include "typedef.h"
#include <qt_windows.h>
#include "ftd2xx.h"

int main ( int argc, char **argv )
{

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);
    QApplication a( argc, argv );
    a.addLibraryPath(a.applicationDirPath()+"/plugins");

//#ifdef FT_DLL
//    FT_STATUS ftStatus;
//    DWORD ftNumDevice;
//    FT_DEVICE_LIST_INFO_NODE *devInfo;
//    FT_HANDLE ftHandle;
//    char FT_Out_Buffer[10];
//    DWORD BytesWritten;
//    DWORD BytesReceived;
//    DWORD BytesReceivedCount;
//    char RxBuffer[256];

//    ftStatus = FT_CreateDeviceInfoList (&ftNumDevice);
//    if (ftStatus==FT_OK)
//    {
//        if(ftNumDevice>0)
//        {
//            devInfo =(FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*ftNumDevice);
//            ftStatus = FT_GetDeviceInfoList(devInfo,&ftNumDevice);
//            if (ftStatus == FT_OK)
//            {
//                FT_Out_Buffer[0] = 'A';
//                FT_Out_Buffer[1] = 'T';
//                FT_Out_Buffer[2] = 0x0d;
//                FT_Out_Buffer[3] = 0x0a;
//                ftStatus = FT_Open(0, &ftHandle);

//                FT_SetBaudRate(ftHandle,9600);
//                FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x00, 0x00);
//                FT_SetDtr(ftHandle);
//                FT_SetRts(ftHandle);

//                qDebug()<<"ftStatus"<<ftStatus;
//                if(ftStatus == FT_OK)
//                {
//                    ftStatus = FT_Write(ftHandle, FT_Out_Buffer, 4,  &BytesWritten);
//                    ftStatus = FT_Write(ftHandle, FT_Out_Buffer, 4,  &BytesWritten);
//                    ftStatus = FT_Write(ftHandle, FT_Out_Buffer, 4,  &BytesWritten);
//                    qDebug()<<"FT_GetQueueStatus"<<FT_GetQueueStatus(ftHandle, &BytesReceivedCount);
//                    BytesReceivedCount = 1;
//                    ftStatus = FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);
//                    qDebug()<<"BytesReceived"<<BytesReceived;
//                    ftStatus = FT_Read(ftHandle,RxBuffer,BytesReceivedCount,&BytesReceived);
//                    qDebug()<<"BytesReceived"<<BytesReceived;
//                    FT_Close(ftHandle);
//                }
//            }
//        }
//    }

//#endif

    MainWindow w;
    w.showMaximized();
    return a.exec();
}
