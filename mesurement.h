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

#include <qwt_plot.h>


class mesurement : public QWidget
{
    Q_OBJECT
public:
    explicit mesurement(QWidget *parent = 0);
    enum ItemDataRole{TypeRole = Qt::UserRole + 1000,
                        SignalValueRole = Qt::UserRole + 1001};

private:
    double AL;
    QwtPlot *pQwt;
    adjview *twPatient;
    adjview *twLens;
    adjview *twVelocity;
    adjview *twMeas;
    sampletable *pSampleTable;
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
    QPushButton *pbMeasure;

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

public slots:
    void changeRow(quint8 idType, quint16 idRow, QString Text);

private slots:
    void changeRow(QList<quint16> extremum);
    void refreshMainParam();
    void changeEye(quint8);
//    void getFileSample();
//    void changeRow(QModelIndex curIndex);
//    void refreshTable(stMainParam);
//    void save();
};

#endif // MESUREMENT_H
