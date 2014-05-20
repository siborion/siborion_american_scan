#include "calculator.h"
#include <QDebug>

calculator::calculator(QWidget *parent) :
    QWidget(parent)
{
    QList<int> columnPercent;
    QStringList lst;


    pBase = scanbase::instanse();

    QStandardItemModel *model;

    QVBoxLayout *layout              = new QVBoxLayout(this);
    QHBoxLayout *layoutTop           = new QHBoxLayout();
    QVBoxLayout *layoutTopLeft       = new QVBoxLayout();
    QGridLayout *layoutTopLeftDown   = new QGridLayout();

    QSpacerItem *vs2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    columnPercent.clear();
    columnPercent<<50<<50;
    twName = new adjview(3, 2, columnPercent);
    model = (QStandardItemModel*)twName->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapName[i]));
        model->setItem(i, 1, new QStandardItem());
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //-------------------------------
    columnPercent.clear();
    columnPercent<<20<<16<<22<<16<<15<<11;
    lst<<"Lens Name"<<"Lens Mfg"<<"Mfg A-Const"<<"pAConst"<<"MfgACD"<<"pACD";
    twLens = new adjview(8, lst, columnPercent);
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
    QString str = "SELECT  name, mfg, aconst, acd from lens;";
    modelMainLens->setQuery(str);
    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
    modelMainLens->setHeaderData(1, Qt::Horizontal, "Mfg", Qt::DisplayRole);
    modelMainLens->setHeaderData(2, Qt::Horizontal, "A-Const", Qt::DisplayRole);
    modelMainLens->setHeaderData(3, Qt::Horizontal, "ACD", Qt::DisplayRole);


    //-------------------------------
    columnPercent.clear();
    columnPercent<<40<<40<<20;
    twK = new adjview(4, 3, columnPercent);
    model = (QStandardItemModel*)twK->model();
    for(quint8 i=0; i<4; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapK[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
        model->setItem(i, 2, i==0?new QStandardItem("mm"):new QStandardItem("D"));
        model->item   (i, 2)->setBackground(Qt::lightGray);
        model->item   (i, 2)->setEditable(false);
    }
    //--------------------------------
    columnPercent.clear();
    columnPercent<<50<<50;
    twA = new adjview(3, 2, columnPercent);
    model = (QStandardItemModel*)twA->model();
    for(quint8 i=0; i<3; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapA[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
    }
    //--------------------------------

    twRx = new adjview(1, 2, columnPercent);
    model = (QStandardItemModel*)twRx->model();
    model->setItem(0, 0, new QStandardItem(baseMapA[3]));
    model->item   (0, 0)->setBackground(Qt::lightGray);
    model->item   (0, 0)->setEditable(false);

    pbOD = new QPushButton("OD");
    pbPersCalc = new QPushButton("Personalized Calculation");

    layoutTopLeftDown->addWidget(twK,  0, 0, 2, 1, Qt::AlignTop);
    layoutTopLeftDown->addWidget(twA,  0, 1, 1, 1, Qt::AlignTop);
    layoutTopLeftDown->addWidget(twRx, 1, 1);
    layoutTopLeftDown->addWidget(pbOD,       2, 0, 2, 1, Qt::AlignTop);
    layoutTopLeftDown->addWidget(pbPersCalc, 2, 1, 1, 1, Qt::AlignTop);

    layoutTopLeft->addWidget(twName);
    layoutTopLeft->addLayout(layoutTopLeftDown);
    layoutTop->addLayout(layoutTopLeft);
    layoutTop->addWidget(twLens, 0, Qt::AlignTop);
    layout->addLayout(layoutTop);

     frCalculator = new QFrame();
     frCalculator->setFrameShape(QFrame::WinPanel);
     frCalculator->setFrameShadow(QFrame::Raised);
     QHBoxLayout *frLayout = new QHBoxLayout(frCalculator);

     Formula1 = new formula();
     Formula2 = new formula();
     Formula3 = new formula();

     frLayout->addWidget(Formula1);
     frLayout->addWidget(Formula2);
     frLayout->addWidget(Formula3);


     layout->addWidget(frCalculator);
     layout->addItem(vs2);

     connect(pbOD, SIGNAL(clicked()), SLOT(changeEye()));
}

void calculator::refreshPatientParam(quint16 id)
{
    QStandardItemModel *model;
    model = (QStandardItemModel*)twK->model();

    QString str = QString("SELECT k1left, k2left, kleft, k1right, k2right, kright FROM patient WHERE id=%1;")
            .arg(id);
    QSqlQuery sql(str);
    if(sql.exec())
    {
        sql.next();
        if(pbOD->text()=="OD")
        {
            model->setData(model->index(1,1), sql.value(0).toString(), Qt::DisplayRole);
            model->setData(model->index(2,1), sql.value(1).toString(), Qt::DisplayRole);
            model->setData(model->index(3,1), sql.value(2).toString(), Qt::DisplayRole);
        }
        else
        {
            model->setData(model->index(1,1), sql.value(3).toString(), Qt::DisplayRole);
            model->setData(model->index(2,1), sql.value(4).toString(), Qt::DisplayRole);
            model->setData(model->index(3,1), sql.value(5).toString(), Qt::DisplayRole);
        }
    }
}

void calculator::changeRow(quint8 numBase, quint16 id, QString Patient, QString Doctor)
{
    QStandardItemModel *model;
    model = (QStandardItemModel*)twName->model();
    model->setData(model->index(0,1), QString("%1").arg(id), Qt::DisplayRole);
    model->setData(model->index(1,1), Patient, Qt::DisplayRole);
    model->setData(model->index(2,1), Doctor, Qt::DisplayRole);
    refreshPatientParam(id);
    refreshTable(id);
}

void calculator::changeEye()
{
    pbOD->setText(pbOD->text()=="OD"?"OS":"OD");
}

void calculator::refreshTable(quint16 id)
{
    QList<int> columnPercent;
    QStringList lst;

    columnPercent.clear();
    columnPercent<<20<<16<<22<<16<<15<<11;
//    lst<<"Lens Name"<<"Lens Mfg"<<"Mfg A-Const"<<"pAConst"<<"MfgACD"<<"pACD";
//    twLens = new adjview(8, lst, columnPercent);
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
    QString str = QString("SELECT lens.name,lens.aconst,lens.acd,lens.sf,doctor_lens.nom_formula FROM patient, doctor_lens, lens ON patient.doctor=doctor_lens.id_doctor AND lens.id=doctor_lens.id_lens WHERE patient.id=%1;").arg(id);
    modelMainLens->setQuery(str);
//    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
//    modelMainLens->setHeaderData(1, Qt::Horizontal, "Mfg", Qt::DisplayRole);
//    modelMainLens->setHeaderData(2, Qt::Horizontal, "A-Const", Qt::DisplayRole);
//    modelMainLens->setHeaderData(3, Qt::Horizontal, "ACD", Qt::DisplayRole);
    qDebug()<<"0000000000000";

    Formula1->setEnabled(false);
    Formula2->setEnabled(false);
    Formula3->setEnabled(false);

    for(quint8 i=0; i<modelMainLens->rowCount() && i<3; i++)
    {
        quint8 nFormula;
        QString lensName, lensAconst, lensAcd, lensFs;
        nFormula   = twLens->model()->itemData(twLens->model()->index(i,4)).value(0).toInt();
        lensName   = twLens->model()->itemData(twLens->model()->index(i,0)).value(0).toString();
        lensAconst = twLens->model()->itemData(twLens->model()->index(i,1)).value(0).toString();
        lensAcd = twLens->model()->itemData(twLens->model()->index(i,2)).value(0).toString();
        lensFs = twLens->model()->itemData(twLens->model()->index(i,3)).value(0).toString();

        qDebug()<<lensName;

        switch (i)
        {
        case 0:
            Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs);
            Formula1->setEnabled(true);
            break;
        case 1:
            Formula2->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs);
            Formula2->setEnabled(true);
            break;
        case 2:
            Formula3->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs);
            Formula3->setEnabled(true);
        default:
            break;
        }
//        nFormula = modelMainLens->itemData(modelMainLens->index(i,6))
//        modelMainLens->itemData()
//        Formula1->setValue(
    }
//    modelMainLens->itemData()
}

void calculator::refreshAl(double AL)
{
    QStandardItemModel *model;
    model = (QStandardItemModel*)twK->model();
    model->setData(model->index(0,1), AL, Qt::DisplayRole);

    qDebug()<<AL;
}

