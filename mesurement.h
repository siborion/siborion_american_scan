#ifndef MESUREMENT_H
#define MESUREMENT_H

#include "bases.h"
#include "scanbase.h"
#include "basefill.h"
#include <QWidget>
#include <qlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QLabel>
#include <adjview.h>
#include <QLineEdit>
#include <QComboBox>
#include "mydelegate.h"
#include "plot.h"
#include "bigviewnum.h"
#include "bigviewnumcur.h"
#include "key_radio.h"
#include "sampletable.h"
#include "QDate"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QTextEdit>
#include "scanbutton.h"
#include "typedef.h"
#include "curentparam.h"
#include "thread.h"
#include "typedef.h"
#include <qt_windows.h>
#include "ftd2xx.h"



#include <qwt_plot.h>


class mesurement : public QWidget
{
    Q_OBJECT
public:
    explicit mesurement(QWidget *parent = 0);
    enum ItemDataRole{TypeRole = Qt::UserRole + 1000,
                        SignalValueRole = Qt::UserRole + 1001};
    sampletable *pSampleTable;

private:

    quint8 countRequest;
    FT_STATUS ftStatus;
    DWORD ftNumDevice;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    FT_HANDLE ftHandle;
    char FT_Out_Buffer[10];
    DWORD BytesWritten;
    DWORD BytesReceived;
    DWORD BytesReceivedCount;
    char RxBuffer[2048];
    bool doDll;


    Thread *thread;
    CurentParam *curentParam;
    quint8 countMeasure;
    quint8 offset;
    QComboBox *cbPort;
    QSerialPort *port;
    QTimer *timer;
    double AL;
    QwtPlot *pQwt;
    adjview *twPatient;
    adjview *twLens;
    adjview *twVelocity;
//    adjview *twMeas;
    key_radio *pKey;
    Plot *pPlot;
    bigviewnum *pBigView;
    bigviewnumcur *pBigViewCur;
    QStandardItemModel *modelPatient;
    QStandardItemModel *modelLens;
    QStandardItemModel *modelVelocity;
    QStandardItemModel *modelMeas;
    QPushButton *pbTest;
    double decRound(double Val, quint8 dec);
    QModelIndex tableIndex;
    void refreshTable(quint8 rowNom, stMainParam mainParam);
    void stopMeasure();
//    LineSelect *lineSelect;

//    QComboBox *VALname;
//    QLineEdit *VALdata;
//    QComboBox *VALdoctor;
//    QSqlTableModel *modelName;
//    QSqlTableModel *modelDoctor;

//    QLineEdit *VALaxial;
//    QLineEdit *VALacd;
//    QLineEdit *VALlt;
//    QLineEdit *VALvit;

//    QLineEdit *VALal;
//    QLineEdit *VALaverage;
//    QLineEdit *VALsd;

    scanbase *pBase;
//    basefill *pBaseFill;

    QPushButton *pbDel;
    ScanButton *pbMeasure;

//    QLabel *average;

    QString baseMapPatient[4] = {
        "Patient ID",
        "Patient Name",
        "Date", 
        "Doctor Name"
        };

    QString baseMapLens[4] = {
        "Axial Length As: ACD+LT+VIT",
        "ACD @ 1532 m/sec",
        "LT @ 1641 m/sec",
        "VIT @ 1532 m/sec"
        };

    QString baseMapVelocity[3] = {
        "AL @ Ave. Velocity 1550 m/sec",
        "Average",
        "SD"
        };

signals:
//    void refreshAl(double);
//    void refreshAcd(double);
    void refreshMeasure(stMeasureParam);

public slots:
//    void changeRow(quint8 idType, quint16 idRow, QString Patient, QString Doctor);

private slots:
    void changeRow(QList<quint16> extremum);
    void refreshMainParam();
//    void changeEye(quint8);
    void openPort();
    void doTimer();
};

#endif // MESUREMENT_H
