#include "formula.h"

formula::formula(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QList<int> columnPercent;
    QStringList lst;

    columnPercent.clear();
    columnPercent<<100;
    lst.clear();
    lst<<"U.D.";
    twHead = new adjview(1, lst, columnPercent);

    columnPercent.clear();
    columnPercent<<33<<33<<34;
    lst.clear();
    lst<<"Formula"<<"IOL"<<"REF";
    twCalculator = new adjview(13, lst, columnPercent);
    twCalculator->setSpan(0,0,10,1);

    lst.clear();
    lst<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay";
    cbFormula = new QComboBox();
    cbFormula->addItems(lst);

//    columnPercent.clear();
//    columnPercent<<100;
//    twVs = new adjview(lst, 1, columnPercent);

//    layout->setVerticalSpacing(0);
    layout->addWidget(cbFormula);
    layout->addWidget(twHead);
    layout->addWidget(twCalculator);
//    layout->addWidget(twVs);
}
