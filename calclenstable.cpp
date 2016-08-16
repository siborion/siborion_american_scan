#include "calclenstable.h"
#include "ui_calclenstable.h"
#include <QDebug>


//CalcLensTable::CalcLensTable(adjview * parent) :
//    adjview(parent)
//{
//    this->setFrameShape(QFrame::NoFrame);
//    this->setFrameShadow(QFrame::Plain);

//    this->setFrameShape(QFrame::Panel);
//    this->setFrameShadow(QFrame::Plain);
//    this->setStyleSheet(QStringLiteral("gridline-color: rgb(10, 10, 17);"));
//}

CalcLensTable::CalcLensTable(int row, int col, QList<int> pr, QTableView *parent):
    adjview(row, col, pr, parent)
{
    QAbstractItemView::EditTriggers triggers = this->editTriggers();
    triggers |= QAbstractItemView::CurrentChanged;
    this->setEditTriggers(triggers);

    QFont font;
    font.setBold(true);

    QModelIndex index;
    tableModel = this->model();

    //    model = this->selectionModel();

    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Plain);
    this->setStyleSheet(QStringLiteral("gridline-color: rgb(200, 200, 255);"));
    this->setSpan(0,0,3,1);
    this->setSpan(3,0,7,1);
    this->setSpan(10,1,1,2);
    this->setSpan(10,3,1,2);
    this->setSpan(10,5,1,2);

    this->verticalHeader()->setDefaultSectionSize(22);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    //    setSide("OD");

    //    index = this->tableModel->index(0,5);
    //    tableModel->setData(index, "Ref", Qt::DisplayRole);

    for(quint8 i=0; i<17; i++)
    {
        for(quint8 j=0; j<11; j++)
        {
            index = this->tableModel->index(i,j);

            tableModel->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

            if(((i==0)||(i==1)||(i==2)||(j==0))||((i>=12)&&((i&1)==0)))
                tableModel->setData(index, QColor(230,230,230,255),Qt::BackgroundColorRole);

            if(i==10)
                tableModel->setData(index, QColor(200,200,200,255),Qt::BackgroundColorRole);


            if((i==6)&&(j>0))
                tableModel->setData(index, QColor(200,200,255,255),Qt::BackgroundColorRole);

            if(((i<2))&&(j>0)&&((j&1)==1))
                this->setSpan(i,j,1,2);

            if((i==2)&&(j>0))
            {
                tableModel->setData(index, font, Qt::FontRole);
                tableModel->setData(index, (j&1)?"IOL":"Ref", Qt::DisplayRole);
            }

            if(i<=2)
                tableModel->setData(index, font, Qt::FontRole);
        }
    }
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));
    pCombo_Delegate.append(new CCombo_Delegate_Cell(this));

    //    pCombo_Delegate.at(0)->values().insert(0, "");

    this->setItemDelegateForColumn(1, pCombo_Delegate.at(0));
    this->setItemDelegateForColumn(3, pCombo_Delegate.at(1));
    this->setItemDelegateForColumn(5, pCombo_Delegate.at(2));

    this->setItemDelegateForColumn(7, pCombo_Delegate.at(3));
    this->setItemDelegateForColumn(9, pCombo_Delegate.at(4));
    //    this->setItemDelegateForColumn(6, pCombo_Delegate.at(5));


    connect(pCombo_Delegate.at(0), SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), SLOT(slChangeCombo1()));
    connect(pCombo_Delegate.at(1), SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), SLOT(slChangeCombo2()));
    connect(pCombo_Delegate.at(2), SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), SLOT(slChangeCombo3()));
    connect(pCombo_Delegate.at(3), SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), SLOT(slChangeCombo4()));
    connect(pCombo_Delegate.at(4), SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), SLOT(slChangeCombo5()));

    //    connect(pCombo_Delegate.at(0), SIGNAL(commitData(QWidget*)), SLOT(slChangeCombo1()));
}

void CalcLensTable::setSide(QString val)
{
    QFont font;
    font.setBold(true);
    QModelIndex index;
    index = this->tableModel->index(0, 0);
    tableModel->setData(index, font, Qt::FontRole);
    tableModel->setData(index, val,  Qt::DisplayRole);
}

void CalcLensTable::setValue(quint8 nomLens, quint8 formula, QString name, QString aconst, QString acd, QString fs, QString a0, QString a1, QString a2, double dK, double dAL, double dACD, double RxVal)
{
    QModelIndex index;
    index = this->tableModel->index(0, nomLens*2+1);
    tableModel->setData(index, name,  Qt::DisplayRole);

    QStringList s;
    s = getListFormula();

    pCombo_Delegate.at(nomLens)->values().insert(1, s.at(1)+"   A-Const: "+aconst);
    pCombo_Delegate.at(nomLens)->values().insert(2, s.at(2)+"   A-Const: "+aconst);
    pCombo_Delegate.at(nomLens)->values().insert(3, s.at(3)+"   ACD: "+acd);
    pCombo_Delegate.at(nomLens)->values().insert(4, s.at(4)+"   SF: "+fs);
    pCombo_Delegate.at(nomLens)->values().insert(5, s.at(5)+"   A-Const: "+aconst);

    AConst[nomLens] = aconst.toDouble();
    ACD[nomLens]    = acd.toDouble();
    SF[nomLens]     = fs.toDouble();
    A0[nomLens]     = a0.toDouble();
    A1[nomLens]     = a1.toDouble();
    A2[nomLens]     = a2.toDouble();
    K[nomLens]      = dK;
    AL[nomLens]     = dAL;
    Rx[nomLens]     = RxVal;
    ACD_measure[nomLens] = dACD;

    quint8 curFormulaIndex;
    index = this->tableModel->index(1, nomLens*2+1);
    curFormulaIndex = tableModel->data(index, Qt::DisplayRole).toUInt();

    //    if(formula != curFormulaIndex)

    //Для того чтоб отрефрешилось при иручном зменении User Defined
    if(formula==1)
        tableModel->setData(index, 2, Qt::DisplayRole);
    else
        tableModel->setData(index, 1, Qt::DisplayRole);
    tableModel->setData(index, formula, Qt::DisplayRole);

    changeFotmula(nomLens, formula);
    //    this->repaint();


    //    qDebug()<<nomLens<<AConst[nomLens];

}

QStringList CalcLensTable::getListFormula()
{
    QStringList slTmp;
    slTmp<<""<<"SRKII"<<"SRK/T"<<"Hoffer Q"<<"Holladay"<<"Haigis";
    return slTmp;
}

void CalcLensTable::changeFotmula(quint8 nomLens, int formula)
{
    calculateIOL(nomLens, formula);
    refreshFormula(nomLens, formula);
}

void CalcLensTable::calculateIOL(quint8 nomLens, quint8 formula)
{
    _formulae stFormula;
    QStandardItemModel *model;// = (QStandardItemModel*)twHead->model();
    switch (formula)
    {
    case 0:
        clearParam(nomLens);
        break;
    case SRKII:
        Calculator(formula, AL[nomLens], AConst[nomLens], K[nomLens], Rx[nomLens], &stFormula);
        saveParam(nomLens, &stFormula);
        break;
    case SRKT:
        Calculator(formula, AL[nomLens], AConst[nomLens], K[nomLens], Rx[nomLens], &stFormula);
        saveParam(nomLens, &stFormula);
        break;
    case HOFFERQ:
        Calculator(formula, AL[nomLens], ACD[nomLens], K[nomLens], Rx[nomLens], &stFormula);
        saveParam(nomLens, &stFormula);
        break;
    case HOLLADAY:
        Calculator(formula, AL[nomLens], SF[nomLens], K[nomLens], Rx[nomLens], &stFormula);
        saveParam(nomLens, &stFormula);
        break;
    case HAIGIS:
        HaigisCalc(A0[nomLens], A1[nomLens], A2[nomLens], AL[nomLens], AConst[nomLens], ACD_measure[nomLens], K[nomLens], Rx[nomLens], &stFormula);
        saveParam(nomLens, &stFormula);
        break;
    }
}

void CalcLensTable::refreshFormula(quint8 nomLens, int curIndex)
{
    _formulae stFormula;
    QModelIndex index;
    quint8 j=0;
    QStringList slTmp;
    slTmp = getListFormula();

    for(quint8 i=1; i<=5; i++)
    {
        j++;
        switch (i)
        {
        case SRKII:   Calculator(i, AL[nomLens], AConst[nomLens], K[nomLens], 0, &stFormula); break;
        case SRKT:    Calculator(i, AL[nomLens], AConst[nomLens], K[nomLens], 0, &stFormula);    break;
        case HOFFERQ: Calculator(i, AL[nomLens], ACD[nomLens],    K[nomLens], 0, &stFormula);     break;
        case HOLLADAY:Calculator(i, AL[nomLens], SF[nomLens],     K[nomLens], 0, &stFormula);     break;
        case HAIGIS:  HaigisCalc(A0[nomLens], A1[nomLens], A2[nomLens], AL[nomLens], AConst[nomLens], ACD_measure[nomLens], K[nomLens], 0, &stFormula);  break;
        }
        if(curIndex==0)
        {
            index = this->tableModel->index(10+j, nomLens*2+1);
            tableModel->setData(index, "", Qt::DisplayRole);
            index = this->tableModel->index(10+j, nomLens*2+2);
            tableModel->setData(index, "", Qt::DisplayRole);
        }
        else
        {
            index = this->tableModel->index(10+j, nomLens*2+1);
            tableModel->setData(index, slTmp.at(i), Qt::DisplayRole);
            index = this->tableModel->index(10+j, nomLens*2+2);
            tableModel->setData(index, QString("EMM = %1").arg(stFormula.PEMM, 0, 'f', 2), Qt::DisplayRole);
        }
    }

    index = this->tableModel->index(2, nomLens*2+1);
    tableModel->setData(index, "IOL", Qt::DisplayRole);
    index = this->tableModel->index(2, nomLens*2+2);
    tableModel->setData(index, "Ref", Qt::DisplayRole);
}


void CalcLensTable::clearParam(quint8 nomLens)
{
    QModelIndex index;
    double dTmp;
    for(quint8 i=0; i<7; i++)
    {
        index = this->tableModel->index(i+3, nomLens*2+1);
        QString str = " ";
        tableModel->setData(index, str, Qt::DisplayRole);
        index = this->tableModel->index(i+3, nomLens*2+2);
        tableModel->setData(index, str, Qt::DisplayRole);
    }
}


void CalcLensTable::saveParam(quint8 nomLens, _formulae *val)
{
    QModelIndex index;
    double dTmp;
    for(quint8 i=0; i<7; i++)
    {
        index = this->tableModel->index(i+3, nomLens*2+1);
        dTmp = val->IOLPower[i];
        QString str = QString("%1").arg(dTmp, 0, 'f', 1);
        tableModel->setData(index, str, Qt::DisplayRole);

        index = this->tableModel->index(i+3, nomLens*2+2);
        dTmp = round(val->PORx[i]*100)/100;
        str = QString("%1").arg(dTmp, 0, 'f', 2);
        tableModel->setData(index, str, Qt::DisplayRole);
    }
}

void CalcLensTable::slChangeCombo1()
{
    QModelIndex index;
    quint8 nomFormula;
    index = this->tableModel->index(1,1);
    nomFormula = tableModel->data(index, Qt::DisplayRole).toUInt();
    changeFotmula(0, nomFormula);
}

void CalcLensTable::slChangeCombo2()
{
    QModelIndex index;
    quint8 nomFormula;
    index = this->tableModel->index(1,3);
    nomFormula = tableModel->data(index, Qt::DisplayRole).toUInt();
    changeFotmula(1, nomFormula);
}

void CalcLensTable::slChangeCombo3()
{
    QModelIndex index;
    quint8 nomFormula;
    index = this->tableModel->index(1,5);
    nomFormula = tableModel->data(index, Qt::DisplayRole).toUInt();
    changeFotmula(2, nomFormula);
}

void CalcLensTable::slChangeCombo4()
{
    QModelIndex index;
    quint8 nomFormula;
    index = this->tableModel->index(1,7);
    nomFormula = tableModel->data(index, Qt::DisplayRole).toUInt();
    changeFotmula(3, nomFormula);
}

void CalcLensTable::slChangeCombo5()
{
    QModelIndex index;
    quint8 nomFormula;
    index = this->tableModel->index(1,9);
    nomFormula = tableModel->data(index, Qt::DisplayRole).toUInt();
    changeFotmula(4, nomFormula);
}

void CalcLensTable::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = this->indexAt(event->pos());
    this->edit(index);
    //    adjview::mousePressEvent(event);
}

void CalcLensTable::clear()
{
    QModelIndex index;

    for(quint8 i=0; i<tableModel->rowCount(); i++)
    {
        for(quint8 j=0; j<tableModel->rowCount(); j++)
        {
            index = this->tableModel->index(i,j);
            tableModel->setData(index, "", Qt::DisplayRole);
        }
    }
    //    tableModel->in
}

CalcLensTable::~CalcLensTable()
{
    delete ui;
}
