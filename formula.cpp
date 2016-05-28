#include "formula.h"
#include <QDebug>
#include <QLabel>
#include <QTableWidgetItem>
#include <QBrush>


formula::formula(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::WinPanel);
    setFrameShadow(QFrame::Raised);
    QGridLayout *layout = new QGridLayout(this);
//    layout->setSpacing(0);
//    layout->setHorizontalSpacing(0);
//    layout->setVerticalSpacing(0);
//    layout->setColumnStretch(0,1);
//    layout->setColumnStretch(1,2);

    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    font.setFamily(QStringLiteral("Arial"));

    lLens = new QLabel("lens");
    lLens->setAlignment(Qt::AlignCenter);
    lLens->setFont(font);
    lLens->setMaximumHeight(30);

    leLens = new QLabel("A-Const");
    leLens->setAlignment(Qt::AlignCenter);
    leLens->setVisible(false);

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
    columnPercent<<33<<33<<34;
    lst.clear();
    lst<<"Formula"<<"IOL"<<"REF";
    twFormula = new adjview(12, lst, columnPercent);
//    twFormula->setStyleSheet(QStringLiteral("gridline-color: rgb(0, 0, 0);"));
//    twFormula->setGridStyle(Qt::SolidLine);

//    twFormula->setFrameStyle(0);
    twFormula->setSpan(0,  0, 7, 1);
    twFormula->setSpan(7, 1, 1,  2);
    twFormula->setSpan(8, 1, 1,  2);
    twFormula->setSpan(9, 1, 1,  2);
    twFormula->setSpan(10, 1, 1,  2);
    twFormula->setSpan(11, 1, 1,  2);

//    twFormula->setFrameStyle(QFrame::Box);
//    twFormula->setFrameStyle(QFrame::StyledPanel);

//    DelegateLens * delegateLens = new DelegateLens();
//    twFormula->setItemDelegate(delegateLens);
//    twFormula->setStyleSheet(QLatin1String("gridline-color: rgba(255, 255, 255);\n""background-color: rgb(200, 200, 200);\n""border-color: rgba(255, 255, 255);"));

    columnPercent.clear();
    columnPercent<<45<<45;
    lst.clear();
    lst<<"IOL"<<"REF";
//    twCalculator = new adjview(10, lst, columnPercent);
    twCalculator = twFormula;
//    twCalculator->setFrameStyle(0);
//    twCalculator->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    quint8 uiHeight;
    uiHeight = twCalculator->height()-2;
    twCalculator->setMinimumHeight(uiHeight);
    twCalculator->setMaximumHeight(uiHeight);

    columnPercent.clear();
    columnPercent<<100;
//    twEmm = new adjview(5, 1, columnPercent);
    twEmm = twFormula;
//    twEmm->setFrameStyle(0);
//    twEmm->setStyleSheet(QLatin1String("gridline-color: rgba(255, 255, 255);\n""background-color: rgb(200, 200, 200);\n" "border-color: rgba(255, 255, 255);"));

    lst.clear();
    lst=getListFormula();
    cbFormula = new QComboBox();
    cbFormula->setStyleSheet(QLatin1String("text-align: center;"));
    cbFormula->addItems(lst);

    cbFormula->setEditable(true);
    cbFormula->lineEdit()->setReadOnly(true);
    cbFormula->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < cbFormula->count(); i++)
        cbFormula->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);


    layout->addWidget(lLens,     0, 0, 1, 2);
    layout->addWidget(cbFormula, 1, 0, 1, 1);
    layout->addWidget(leLens,    1, 1, 1, 1);
    layout->addWidget(twFormula, 2, 0, 1, 2);

    connect(cbFormula, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFotmula(int)));
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
        j++;
        switch (i)
        {
        case SRKII:   Calculator(i, AL, AConst, K, 0, &stFormula); break;
        case SRKT:    Calculator(i, AL, AConst, K, 0, &stFormula);    break;
        case HOFFERQ: Calculator(i, AL, ACD,    K, 0, &stFormula);     break;
        case HOLLADAY:Calculator(i, AL, SF,     K, 0, &stFormula);     break;
        case HAIGIS:  HaigisCalc(A0, A1, A2, AL, AConst, ACD_measure, K, 0, &stFormula);  break;
        }
        model1->setItem(6+j, 1, getItem(stFormula.PEMM, Qt::AlignCenter));
        model->setItem (6+j, 0, getItem(slTmp.at(i),    Qt::AlignCenter));
    }
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

void formula::setValue(quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal)
{

//    qDebug()<<"nm"<<name;

    QStringList s;
    s = getListFormula();

    cbFormula->setItemText(1, s.at(1)+"   A_Const: "+aconst);
    cbFormula->setItemText(2, s.at(2)+"   A_Const: "+aconst);
    cbFormula->setItemText(3, s.at(3)+"   ACD: "+acd);
    cbFormula->setItemText(4, s.at(4)+"   SF: "+fs);
    cbFormula->setItemText(5, s.at(5)+"   A_Const: "+aconst);

    AConst = aconst.toDouble();
    ACD = acd.toDouble();
    SF = fs.toDouble();
    A0 = a0.toDouble();
    A1 = a1.toDouble();
    A2 = a2.toDouble();
    K = dK;
    AL = dAL;
    Rx = RxVal;
    ACD_measure = dACD;
    lLens->setText(name);

    if(formula==cbFormula->currentIndex())
        changeFotmula(formula);
    else
        cbFormula->setCurrentIndex(formula);
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
        Calculator(formula, AL, AConst, K, Rx, &stFormula);
        break;
    case SRKT:
        Calculator(formula, AL, AConst, K, Rx, &stFormula);
        break;
    case HOFFERQ:
        Calculator(formula, AL, ACD, K, Rx, &stFormula);
        break;
    case HOLLADAY:
        Calculator(formula, AL, SF, K, Rx, &stFormula);
        break;
    case HAIGIS:
//        Calculator(formula, AL, AConst, K, ACD_measure, &stFormula);
        HaigisCalc(A0, A1, A2, AL, AConst, ACD_measure, K, Rx, &stFormula);
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
    QModelIndex index1, index2;
    double dTmp;
    QBrush hhh;
    hhh.setColor(Qt::red);
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem  *item;
    model = (QStandardItemModel*)twCalculator->model();
    for(quint8 i=0; i<7; i++)
    {

        dTmp = val->IOLPower[i];
        QString str = QString("%1").arg(dTmp, 0, 'f', 1);
        QStandardItem *sTmp1 = new QStandardItem(str);
        sTmp1->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, sTmp1);
        dTmp = round(val->PORx[i]*100)/100;
        str = QString("%1").arg(dTmp, 0, 'f', 2);
        QStandardItem *sTmp2 = new QStandardItem(str);
        sTmp2->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 2, sTmp2);

        if(i==3)
        {
            index1 = model->index(i,1);
            index2 = model->index(i,2);
            QColor color;
            color.setRgb(0,255,0);
            model->setData(index1,color,Qt::BackgroundRole);
            model->setData(index2,color,Qt::BackgroundRole);
        }
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

void formula::clear()
{
    QStandardItemModel *model;
    model = (QStandardItemModel*)twFormula->model();
    model->setRowCount(0);
}
