#include "formula.h"
#include <QDebug>

formula::formula(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,2);

    QList<int> columnPercent;
    QStringList lst;

    columnPercent.clear();
    columnPercent<<100;
    lst.clear();
    lst<<"CN50SM / Alcon";
    twHead = new adjview(1, lst, columnPercent);
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twHead->model();
    model->setItem(0, 0, getItem(QString("A-Const = 116.5"), Qt::AlignRight));

    columnPercent.clear();
    columnPercent<<100;
    lst.clear();
    lst<<"Formula";
    twFormula = new adjview(14, lst, columnPercent);
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
    twEmm = new adjview(4, 1, columnPercent);
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

    layout->addWidget(cbFormula, 0, 0, 1, 2);
    layout->addWidget(twHead,    1, 0, 1, 2);

    layout->addWidget(twFormula,    2, 0, 2, 1);
    layout->addWidget(twCalculator, 2, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(twEmm, 3, 1, 1, 1, Qt::AlignTop);

    connect(cbFormula, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshFormula()));
    refreshFormula();
}

void formula::refreshFormula(void)
{
    quint8 curIndex, j=0;
    QStringList slTmp;
    slTmp = getListFormula();
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twFormula->model();
    curIndex = cbFormula->currentIndex();
    model->setItem(0, 0, getItem(slTmp.at(curIndex), Qt::AlignCenter));
    for(quint8 i=0; i<4; i++)
    {
        if(curIndex != i)
        {
            j++;
            model->setItem(10+j, 0, getItem(slTmp.at(i), Qt::AlignCenter));
        }
    }
}

QStringList formula::getListFormula()
{
    QStringList slTmp;
    slTmp<<""<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay";
    return slTmp;
}

QStandardItem* formula::getItem(QString val, Qt::AlignmentFlag align)
{
    QStandardItem *siTmp = new QStandardItem(val);
    siTmp->setTextAlignment(align);
    return siTmp;
}

void formula::setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, double dK, double dAL)
{
    QStringList lensName;
    _formulae stFormula;
    lensName<<name;

    cbFormula->setCurrentIndex(formula);
    QStandardItemModel *model = (QStandardItemModel*)twHead->model();
    model->setHorizontalHeaderLabels(lensName);

    qDebug() << "000000000000000000000";
    AConst = aconst.toDouble();
    qDebug() << "AConst" << AConst ;
    ACD = acd.toDouble();
    qDebug() << "ACD" << ACD ;
    SF = fs.toDouble();
    qDebug() << "SF" << SF ;
    K = dK;
    qDebug() << "K" << K ;
    AL = dAL;
    qDebug() << "AL" << AL ;
    qDebug() << "111111111111111111111";

    switch (formula)
    {
    case 0:
    case 1:
        model->setData(twHead->model()->index(0,0),aconst,Qt::DisplayRole);
        Calculator(formula, AL, AConst, K, 0, &stFormula);
        break;
    case 2:
        model->setData(twHead->model()->index(0,0),acd,Qt::DisplayRole);
        Calculator(formula, AL, ACD, K, 0, &stFormula);
        break;
    case 3:
        model->setData(twHead->model()->index(0,0),fs,Qt::DisplayRole);
        Calculator(formula, AL, SF, K, 0, &stFormula);
        break;
    }

    model = (QStandardItemModel*)twCalculator->model();
    qDebug()<<"888";
    for(quint8 i=0; i<5; i++)
    {
        QStandardItem *sTmp1 = new QStandardItem(QString("%1").arg(stFormula.IOLPower[i]));
        model->setItem(i, 0, sTmp1);
        QStandardItem *sTmp2 = new QStandardItem(QString("%1").arg(stFormula.PORx[i]));
        model->setItem(i, 1, sTmp2);
    }


}


void formula::saveParam(_formulae *val)
{
    QStandardItemModel *model = new QStandardItemModel();
    model = (QStandardItemModel*)twCalculator->model();
    qDebug()<<"888";
    for(quint8 i=0; i<5; i++)
    {
        QStandardItem *sTmp1 = new QStandardItem(QString("%1").arg(val->IOLPower[i]));
        model->setItem(i, 0, sTmp1);
        QStandardItem *sTmp2 = new QStandardItem(QString("%1").arg(val->PORx[i]));
        model->setItem(i, 1, sTmp2);
    }
}
