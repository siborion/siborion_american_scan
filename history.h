#ifndef history_H
#define history_H

#include "scanbase.h"
#include "basefill.h"
#include <QWidget>
#include <qlayout.h>
#include <QTableWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
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
#include "bigviewnumhor.h"
#include "key_radio.h"

#include <qwt_plot.h>


class history : public QWidget
{
    Q_OBJECT
public:
    explicit history(QWidget *parent = 0);
    enum ItemDataRole{TypeRole = Qt::UserRole + 1000,
                        SignalValueRole = Qt::UserRole + 1001};

private:
    QTreeWidgetItem* addItem(QString name);
    QTreeWidgetItem* addItem(QTreeWidgetItem* item, QString name);
    QTreeWidget *treeWidget;
    double AL;
    QwtPlot *pQwt;
//    adjview *twPatient;
//    adjview *twLens;
//    adjview *twVelocity;
    adjview *twMeas;
    Plot *pPlot;
    bigviewnumhor *pBigView;
//    QStandardItemModel *modelPatient;
//    QStandardItemModel *modelLens;
//    QStandardItemModel *modelVelocity;
//    QStandardItemModel *modelMeas;
//    QPushButton *pbTest;
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

    scanbase *pBase;
    basefill *pBaseFill;




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
    void save();
};

#endif // history_H
