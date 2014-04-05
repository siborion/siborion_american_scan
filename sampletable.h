#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <adjview.h>
#include <QFileDialog>
#include "plot.h"

class sampletable : public QWidget
{
    Q_OBJECT
public:
    explicit sampletable(QWidget *parent = 0);
//    QHash<quint16, quint8> hSample;
    stMainParam mainParam;
    QByteArray baSample;

private:
    double AL;
    QList<quint16> allExtremum;
    adjview *twMeas;
    bool findExtremum(QByteArray *Sample, QList<quint16> &extremum);
    bool findMainParam(QList<quint16> *extremum, stMainParam &mainParam);
    void refreshTable(quint8 rowNom, stMainParam mainParam);
    double decRound(double Val, quint8 dec);
    QModelIndex tableIndex;

signals:
    void changeRow();

public slots:
    void getFileSample();
    void refreshTable(stMainParam mainParam);
    void changeRow(QModelIndex curIndex);

};

#endif // SAMPLETABLE_H
