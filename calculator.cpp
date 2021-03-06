#include "calculator.h"
#include "calc.h"
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
    columnPercent<<20<<20<<20<<20<<20;
    lst<<"Lens Name"<<"AConst"<<"ACD"<<"SF"<<"FORMULA";
    twLens = new adjview(8, lst, columnPercent);
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
//    QString str = "SELECT  name, mfg, aconst, acd from lens;";
    QString str = QString("SELECT lens.name as 'Lens Name',lens.aconst,lens.acd,lens.sf,doctor_lens.nom_formula FROM patient, doctor_lens, lens ON patient.doctor=doctor_lens.id_doctor AND lens.id=doctor_lens.id_lens WHERE 0=1;");
    modelMainLens->setQuery(str);
    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
    modelMainLens->setHeaderData(1, Qt::Horizontal, "AConst", Qt::DisplayRole);
    modelMainLens->setHeaderData(2, Qt::Horizontal, "ACD", Qt::DisplayRole);
    modelMainLens->setHeaderData(3, Qt::Horizontal, "SF", Qt::DisplayRole);
    modelMainLens->setHeaderData(4, Qt::Horizontal, "FORMULA", Qt::DisplayRole);


    //-------------------------------
//    QFont font;
//    font.setStyle();

    columnPercent.clear();
    columnPercent<<40<<40<<20;
    twK = new adjview(5, 3, columnPercent);
    model = (QStandardItemModel*)twK->model();
    for(quint8 i=0; i<5; i++)
    {
        model->setItem(i, 0, new QStandardItem(baseMapK[i]));
        model->item   (i, 0)->setBackground(Qt::lightGray);
        model->item   (i, 0)->setEditable(false);
        model->item   (i, 0)->setEnabled(false);
        model->setItem(i, 2, i==0?new QStandardItem("mm"):new QStandardItem("D"));
        model->item   (i, 2)->setBackground(Qt::lightGray);
//        model->item   (i, 2)->setFont(font);
        model->item   (i, 2)->setEditable(false);
        model->item   (i, 2)->setEnabled(false);

    }
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
//    palette.setBrush(QPalette::Active, QPalette::Text, brush);
//    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
//    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
//    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    twK->setPalette(palette);


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
     connect(twK->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),  SLOT(setAL(QModelIndex,QModelIndex)));
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
            model->setData(model->index(1,1), sql.value(0).toDouble(), Qt::DisplayRole);
            model->setData(model->index(2,1), sql.value(1).toDouble(), Qt::DisplayRole);
            model->setData(model->index(3,1), sql.value(2).toDouble(), Qt::DisplayRole);
        }
        else
        {
            model->setData(model->index(1,1), sql.value(3).toDouble(), Qt::DisplayRole);
            model->setData(model->index(2,1), sql.value(4).toDouble(), Qt::DisplayRole);
            model->setData(model->index(3,1), sql.value(5).toDouble(), Qt::DisplayRole);
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
    patientCurId = id;
    refreshPatientParam(patientCurId);
    refreshTable(patientCurId);
}

void calculator::changeEye()
{
//    double K;
    pbOD->setText(pbOD->text()=="OD"?"OS":"OD");

//    QStandardItemModel *model;
//    model = (QStandardItemModel*)twK->model();
//    model->setData(model->index(3,1), sql.value(2).toString(), Qt::DisplayRole);


    Calculator(0, 12, 1, 2, 0, &stFormula);
//    Calculator(0, 12, 1, 2, 0, &stFormula);
    Formula1->saveParam(&stFormula);
}

void calculator::refreshTable(quint16 id)
{
    QList<int> columnPercent;
    QStringList lst;

    columnPercent.clear();
    columnPercent<<20<<16<<22<<16<<15<<11;
//    lst<<"Lens Name"<<"Lens Mfg"<<"Mfg A-Const"<<"pAConst"<<"MfgACD"<<"pACD";
//    twLens = new adjview(8, lst, columnPercent);
//  <<"AConst"<<"ACD"<<"SF"<<"FORMULA";
    modelMainLens = new QSqlQueryModel ();
    twLens->setModel(modelMainLens);
    QString str = QString("SELECT lens.name as 'Lens Name',lens.aconst,lens.acd,lens.sf,doctor_lens.nom_formula FROM patient, doctor_lens, lens ON patient.doctor=doctor_lens.id_doctor AND lens.id=doctor_lens.id_lens WHERE patient.id=%1;").arg(id);
    modelMainLens->setQuery(str);

    modelMainLens->setHeaderData(0, Qt::Horizontal, "Lens Name", Qt::DisplayRole);
    modelMainLens->setHeaderData(1, Qt::Horizontal, "AConst", Qt::DisplayRole);
    modelMainLens->setHeaderData(2, Qt::Horizontal, "ACD", Qt::DisplayRole);
    modelMainLens->setHeaderData(3, Qt::Horizontal, "SF", Qt::DisplayRole);
    modelMainLens->setHeaderData(4, Qt::Horizontal, "FORMULA", Qt::DisplayRole);

    Formula1->setEnabled(false);
    Formula2->setEnabled(false);
    Formula3->setEnabled(false);

    for(quint8 i=0; i<modelMainLens->rowCount() && i<3; i++)
    {
        double K, AL_meausre;
        quint8 nFormula;
        QString lensName, lensAconst, lensAcd, lensFs;
        nFormula   = twLens->model()->itemData(twLens->model()->index(i,4)).value(0).toInt();
        lensName   = twLens->model()->itemData(twLens->model()->index(i,0)).value(0).toString();
        lensAconst = twLens->model()->itemData(twLens->model()->index(i,1)).value(0).toString();
        lensAcd = twLens->model()->itemData(twLens->model()->index(i,2)).value(0).toString();
        lensFs = twLens->model()->itemData(twLens->model()->index(i,3)).value(0).toString();
        K  = twK->model()->itemData(twK->model()->index(3,1)).value(0).toDouble();
        AL_meausre = twK->model()->itemData(twK->model()->index(0,1)).value(0).toDouble();
        ACD_measure = twK->model()->itemData(twK->model()->index(4,1)).value(0).toDouble();

//        K=1;
//        AL = 20;


        switch (i)
        {
        case 0:
            Formula1->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, K, AL_meausre,ACD_measure);
            Formula1->setEnabled(true);
            break;
        case 1:
            Formula2->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, K, AL_meausre,ACD_measure);
            Formula2->setEnabled(true);
            break;
        case 2:
           Formula3->setValue(nFormula, lensName, lensAconst, lensAcd, lensFs, K, AL_meausre,ACD_measure);
           Formula3->setEnabled(true);
        default:
            break;
        }

        qDebug() << "ACD_measure2" << ACD_measure;

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
}

void calculator::refreshAcd(double Acd)
{
    ACD_measure = Acd;
    qDebug() << "ACD_measure1" << ACD_measure;

    QStandardItemModel *model;
    model = (QStandardItemModel*)twK->model();
    model->setData(model->index(4,1), Acd, Qt::DisplayRole);


}

void calculator::setAL(QModelIndex val1, QModelIndex val2)
{
    double dTmp;
    if(val1.column()==1)
    {
        if ((val1.row()==0) || (val1.row()==3) || (val1.row()==4))
            refreshTable(patientCurId);
        else
        {
            QStandardItemModel *model;
            model = (QStandardItemModel*)twK->model();
            dTmp =  twK->model()->itemData(twK->model()->index(1,1)).value(0).toDouble();
            dTmp += twK->model()->itemData(twK->model()->index(2,1)).value(0).toDouble();
            dTmp /= 2;
            model->setData(model->index(3, 1), dTmp, Qt::DisplayRole);
        }
    }
}

