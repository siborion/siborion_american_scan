#include "formula.h"
#include <QDebug>
#include <QLabel>

formula::formula(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,2);

    lLens = new QLabel("lens");
    leLens = new QLineEdit();
//    lFormula->setText("formula");

    QList<int> columnPercent;
    QStringList lst;

//    columnPercent.clear();
//    columnPercent<<100;
//    lst.clear();
//    lst<<"CN50SM / Alcon";
//   twHead = new adjview(1, lst, columnPercent);
//    QStandardItemModel *model = new QStandardItemModel();
//    model = (QStandardItemModel*)twHead->model();
//    model->setItem(0, 0, getItem(QString("A-Const = 116.5"), Qt::AlignRight));

    columnPercent.clear();
    columnPercent<<100;
    lst.clear();
    lst<<"Formula";
    twFormula = new adjview(15, lst, columnPercent);
    twFormula->setFrameStyle(0);
    twFormula->setSpan(0, 0, 11, 1);
    twFormula->setStyleSheet(QLatin1String("gridline-color: rgba(255, 255, 255);\n"
                                           "background-color: rgb(200, 200, 200);\n"
                                           "border-color: rgba(255, 255, 255);"));

    columnPercent.clear();
    columnPercent<<45<<45;
    lst.clear();
    lst<<"IOL"<<"REF";
    twCalculator = new adjview(10, lst, columnPercent);
    twCalculator->setFrameStyle(0);
    twCalculator->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    quint8 uiHeight;
    uiHeight = twCalculator->height()-2;
    twCalculator->setMinimumHeight(uiHeight);
    twCalculator->setMaximumHeight(uiHeight);

    columnPercent.clear();
    columnPercent<<100;
    twEmm = new adjview(5, 1, columnPercent);
    twEmm->setFrameStyle(0);
    twEmm->setStyleSheet(QLatin1String("gridline-color: rgba(255, 255, 255);\n"
                                           "background-color: rgb(200, 200, 200);\n"
                                           "border-color: rgba(255, 255, 255);"));

    lst.clear();
    lst=getListFormula();
    cbFormula = new QComboBox();
    cbFormula->setStyleSheet(QLatin1String("text-align: right;"));
    cbFormula->addItems(lst);
    cbFormula->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);
    cbFormula->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
    cbFormula->setItemData(2, Qt::AlignCenter, Qt::TextAlignmentRole);
    cbFormula->setItemData(3, Qt::AlignCenter, Qt::TextAlignmentRole);
    cbFormula->setItemData(4, Qt::AlignCenter, Qt::TextAlignmentRole);
    cbFormula->setItemData(5, Qt::AlignCenter, Qt::TextAlignmentRole);

    layout->addWidget(cbFormula, 0, 0, 1, 2);
//    layout->addWidget(twHead,    1, 0, 1, 2);
    layout->addWidget(lLens,    1, 0, 1, 1);
    layout->addWidget(leLens,   1, 1, 1, 1);

    layout->addWidget(twFormula,    2, 0, 4, 1);
    layout->addWidget(twCalculator, 3, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(twEmm, 4, 1, 1, 1, Qt::AlignTop);

    connect(cbFormula, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFotmula(int)));
//    refreshFormula();
}

void formula::refreshFormula(int curIndex)
{
    _formulae stFormula;
    quint8 j=0;
    QStringList slTmp;
    slTmp = getListFormula();
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twFormula->model();

    QStandardItemModel *model1 = new QStandardItemModel();
    model1 = (QStandardItemModel*)twEmm->model();

    model->setItem(0, 0, getItem(slTmp.at(curIndex), Qt::AlignCenter));
    for(quint8 i=1; i<=5; i++)
    {
        if(curIndex != i)
        {
            j++;
            switch (i)
            {
            case SRKII:   Calculator(i, AL, AConst, K, 0, &stFormula); break;
            case SRKT:    Calculator(i, AL, AConst, K, 0, &stFormula);    break;
            case HOFFERQ: Calculator(i, AL, ACD, K, 0, &stFormula);     break;
            case HOLLADAY:Calculator(i, AL, SF, K, 0, &stFormula);     break;
            case HAIGIS:  Calculator(i, AL, AConst, K, ACD_measure, &stFormula);  break;

            }
            model1->setItem(j, 0, getItem(stFormula.PEMM, Qt::AlignCenter));
            model->setItem(10+j, 0, getItem(slTmp.at(i), Qt::AlignCenter));
        }
    }
//    calculateIOL(curIndex);
}

QStringList formula::getListFormula()
{
    QStringList slTmp;
    slTmp<<""<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay"<<"Haigis";
    return slTmp;
}

QStandardItem* formula::getItem(QString val, Qt::AlignmentFlag align)
{
    QStandardItem *siTmp = new QStandardItem(val);
    siTmp->setTextAlignment(align);
    return siTmp;
}

QStandardItem* formula::getItem(double val, Qt::AlignmentFlag align)
{
    QString str = QString("(EMM) %1").arg(val, 0, 'f', 2);
    QStandardItem *siTmp = new QStandardItem(str);
    siTmp->setTextAlignment(align);
    return siTmp;
}

void formula::setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, double dK, double dAL, double dACD)
{
    AConst = aconst.toDouble();
    ACD = acd.toDouble();
    SF = fs.toDouble();
    K = dK;
    AL = dAL;
    ACD_measure = dACD;
    lLens->setText(name);

    qDebug()<<"formula0";
    qDebug()<<formula;
    if(formula==cbFormula->currentIndex())
        changeFotmula(formula);
    else
        cbFormula->setCurrentIndex(formula);
    //    cbFormula->setCurrentIndex(1);
//    qDebug()<<cbFormula->currentIndex();

    qDebug()<<"formula1";


    qDebug()<<"formula2";


    qDebug()<<"formula1";
//    changeFotmula(formula);
    qDebug()<<"formula2";
}

void formula::calculateIOL(quint8 formula)
{

    _formulae stFormula;
    QStandardItemModel *model;// = (QStandardItemModel*)twHead->model();
    switch (formula)
    {
    case 0:
        break;
    case SRKII:
        Calculator(formula, AL, AConst, K, 0, &stFormula);
        break;
    case SRKT:
        Calculator(formula, AL, AConst, K, 0, &stFormula);
        break;
    case HOFFERQ:
        Calculator(formula, AL, ACD, K, 0, &stFormula);
        break;
    case HOLLADAY:
        Calculator(formula, AL, SF, K, 0, &stFormula);
        break;
    case HAIGIS:
        Calculator(formula, AL, AConst, K, ACD_measure, &stFormula);
        break;

    }

    saveParam(&stFormula);

    model = (QStandardItemModel*)twCalculator->model();
    model = (QStandardItemModel*)twEmm->model();
    QString str = QString("(EMM) %1").arg(round(stFormula.PEMM*100)/100, 0, 'f', 2);
    QStandardItem *sTmp3 = new QStandardItem(str);
    sTmp3->setTextAlignment(Qt::AlignCenter);
    model->setItem(0, 0, sTmp3);

}


void formula::saveParam(_formulae *val)
{
    double dTmp;
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twCalculator->model();
    for(quint8 i=0; i<7; i++)
    {

        dTmp = val->IOLPower[i];
        QString str = QString("%1").arg(dTmp, 0, 'f', 1);
        QStandardItem *sTmp1 = new QStandardItem(str);
        sTmp1->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 0, sTmp1);
        dTmp = round(val->PORx[i]*100)/100;
        str = QString("%1").arg(dTmp, 0, 'f', 2);
        QStandardItem *sTmp2 = new QStandardItem(str);
        sTmp2->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, sTmp2);
    }
}

void formula::changeFotmula(int formula)
{
    calculateIOL(formula);
    refreshFormula(formula);

//    QStandardItemModel *model = new QStandardItemModel();
//    model = (QStandardItemModel*)twHead->model();
    switch (formula)
    {
    case SRKII:
//        model->setItem(0, 0, getItem(QString("A-Const = %1").arg(AConst), Qt::AlignRight));
        leLens->setText(QString("A-Const = %1").arg(AConst));
//        leLens->setText("test");
        break;
    case SRKT:
//        model->setItem(0, 0, getItem(QString("A-Const = %1").arg(AConst), Qt::AlignRight));
        leLens->setText(QString("A-Const = %1").arg(AConst));
        break;
    case HOFFERQ:
//        model->setItem(0, 0, getItem(QString("ACD = %1").arg(ACD), Qt::AlignRight));
        leLens->setText(QString("ACD = %1").arg(ACD));
        break;
    case HOLLADAY:
//        model->setItem(0, 0, getItem(QString("SF = %1").arg(SF), Qt::AlignRight));
        leLens->setText(QString("SF = %1").arg(SF));
        break;
    case HAIGIS:
//        model->setItem(0, 0, getItem(QString("SF = %1").arg(SF), Qt::AlignRight));
        leLens->setText(QString("A-Const = %1").arg(AConst));
        break;
    }
}

stFormulaInfo *formula::getModel()
{
//stFormulaInfo stTmp;
//    return (QStandardItemModel*)twCalculator->model();
    stInfo.lensName = cbFormula->currentText();
//    stInfo.formulaName =
    stInfo.model = (QStandardItemModel*)twCalculator->model();
return &stInfo;
}
