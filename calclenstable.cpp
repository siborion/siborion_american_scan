#include "calclenstable.h"
#include "ui_calclenstable.h"
#include "combo_delegate_cell.h"
#include <QDebug>


CalcLensTable::CalcLensTable(adjview * parent) :
    adjview(parent)
{
//    ui->setupUi(this);
//    this->row
    this->setFrameShape(QFrame::NoFrame);
    this->setFrameShadow(QFrame::Plain);

    this->setFrameShape(QFrame::Panel);
    this->setFrameShadow(QFrame::Plain);
    this->setStyleSheet(QStringLiteral("gridline-color: rgb(10, 10, 17);"));

}

CalcLensTable::CalcLensTable(int row, int col, QList<int> pr, QTableView *parent):
    adjview(row, col, pr, parent)
{
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

    this->verticalHeader()->setDefaultSectionSize(16);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    setSide("OD");

    index = this->tableModel->index(0,5);
    tableModel->setData(index, "Ref", Qt::DisplayRole);

    for(quint8 i=0; i<17; i++)
    {
        for(quint8 j=0; j<7; j++)
        {
            index = this->tableModel->index(i,j);

            tableModel->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

            if(((i==0)||(i==1)||(i==2)||(j==0))||((i>=10)&&((i&1)==0)))
                tableModel->setData(index, QColor(230,230,230,255),Qt::BackgroundColorRole);

            if((i==6)&&(j>0))
                tableModel->setData(index, QColor(230,230,255,255),Qt::BackgroundColorRole);

            if(((i<2)||(i>=10))&&(j>0)&&((j&1)==1))
                this->setSpan(i,j,1,2);

            if((i==2)&&(j>0))
            {
                tableModel->setData(index, font, Qt::FontRole);
                tableModel->setData(index, (j&1)?"IOL":"Ref", Qt::DisplayRole);
            }
        }
    }
    CCombo_Delegate_Cell * pCombo_Delegate = new CCombo_Delegate_Cell(this);
    pCombo_Delegate->values().insert( 0, " " );
    pCombo_Delegate->values().insert( 1, "SRK II" );
    pCombo_Delegate->values().insert( 2, "SRK T" );
    pCombo_Delegate->values().insert( 3, "HOFFER Q" );
    pCombo_Delegate->values().insert( 4, "HOLLADAY" );
    pCombo_Delegate->values().insert( 5, "HAIGIS" );
//    ui->tableView->setItemDelegateForColumn(5, pCombo_Delegate);
    this->setItemDelegateForColumn(5, pCombo_Delegate);
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

    qDebug()<<"name"<<name;
    QFont font;
    font.setBold(true);
    QModelIndex index;
    index = this->tableModel->index(0, nomLens*2+1);
    tableModel->setData(index, font, Qt::FontRole);
    tableModel->setData(index, name,  Qt::DisplayRole);

//    QStringList s;
//    s = getListFormula();

//    cbFormula->setItemText(1, s.at(1)+"   A_Const: "+aconst);
//    cbFormula->setItemText(2, s.at(2)+"   A_Const: "+aconst);
//    cbFormula->setItemText(3, s.at(3)+"   ACD: "+acd);
//    cbFormula->setItemText(4, s.at(4)+"   SF: "+fs);
//    cbFormula->setItemText(5, s.at(5)+"   A_Const: "+aconst);
}


CalcLensTable::~CalcLensTable()
{
    delete ui;
}
