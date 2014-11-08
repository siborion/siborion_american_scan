#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include <QStandardItem>
#include "plot.h"
#include "curentparam.h"
#include "parserfront.h"

class sampletable : public QWidget
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0);
    bool findExtremum(QByteArray *Sample, QList<quint16> &extremum, stMainParam &mainParam);
//    bool findMainParam(QList<quint16> *extremum, stMainParam &mainParam);
    void addSampleToTable();
    void addSampleToTable(QByteArray Sample, stMainParam curMainParam, bool newRecord);
//    QHash<quint16, quint8> hSample;
    stMainParam mainParam;
    QByteArray baSample;
    QList<quint16> allExtremum;
    stResultParam resultParam;
    adjview *twMeas;
    stPrintSample printSample();
    void goToLastSample();

private:
    double AL;
//    bool findMainParam(QList<quint16> *extremum, stMainParam &mainParam);
    void refreshTable(quint8 rowNom, stMainParam mainParam);
    double decRound(double Val, quint8 dec, quint16 speed);
    QModelIndex tableIndex;
    void refreshResult(quint8 rowNom);
    CurentParam *curentParam;
//    delegate_sample *delegate;
    QStandardItemModel *modelOD;
    QStandardItemModel *modelOS;
    parserFront *parseCornea;
    parserFront *parseLens;
    parserFront *parseRetina;


signals:
    void changeRow(QList<quint16> extremum);
    void refreshMainParam();

public slots:
    void getFileSample();
    void refreshTable(stMainParam mainParam);
    void changeRow(QModelIndex curIndex);
    void delSample();
    void changeSide();
    void clearModel();
    void changeKeySlot();


};

#endif // SAMPLETABLE_H
