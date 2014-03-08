#ifndef MESUREMENT_H
#define MESUREMENT_H

#include <QWidget>
#include <qlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QFileDialog>
//#include "scanplot.h"
#include <adjview.h>
#include "mydelegate.h"
#include "plot.h"
#include "bigview.h"

#include <qwt_plot.h>


class mesurement : public QWidget
{
    Q_OBJECT
public:
    explicit mesurement(QWidget *parent = 0);
    enum ItemDataRole{TypeRole = Qt::UserRole + 1000,
                        SignalValueRole = Qt::UserRole + 1001};

private:
    QwtPlot *pQwt;
    adjview *twPatient;
    adjview *twLens;
    adjview *twVelocity;
    adjview *twMeas;
    Plot *pPlot;
    bigview *lcdView;
    QStandardItemModel *modelPatient;
    QStandardItemModel *modelLens;
    QStandardItemModel *modelVelocity;
    QStandardItemModel *modelMeas;
    QPushButton *pbTest;
    double decRound(double Val, quint8 dec);
    QModelIndex tableIndex;
//    bool checkSample(QByteArray *Sample, QList<quint16> &extremum);
//    bool findMainParam(QList<quint16> *extremum, QList<quint16> &mainParam);
    void refreshTable(quint8 rowNom, stMainParam mainParam);
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

private slots:
    void getFileSample();
    void changeRow(QModelIndex curIndex);
    void refreshTable(stMainParam);
};

#endif // MESUREMENT_H
