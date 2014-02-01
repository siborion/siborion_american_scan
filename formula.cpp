#include "formula.h"

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
    lst<<"CN50SM / Alcon / A-Const = 116.5";
    twHead = new adjview(1, lst, columnPercent);

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
    cbFormula->addItems(lst);

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
    model->setItem(0, 0, getItem(slTmp.at(curIndex)));
    for(quint8 i=0; i<4; i++)
    {
        if(curIndex != i)
        {
            j++;
            model->setItem(10+j, 0, getItem(slTmp.at(i)));
        }
    }
}

QStringList formula::getListFormula()
{
    QStringList slTmp;
    slTmp<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay";
    return slTmp;
}

QStandardItem* formula::getItem(QString val)
{
    QStandardItem *siTmp = new QStandardItem(val);
    siTmp->setTextAlignment(Qt::AlignCenter);
    return siTmp;
}
