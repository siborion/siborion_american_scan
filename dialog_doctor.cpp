#include "dialog_doctor.h"
#include "ui_dialog_doctor.h"

Dialog_Doctor::Dialog_Doctor(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Doctor)
{
    QList<int> columnPercent;
    QStringList lst;
    quint16 tableWidth;

    curId = id;

    ui->setupUi(this);

//    pBaseFill = new basefill(id, children(), (QString)"doctor");
//    pBaseFill->fillData();

    model = new QStandardItemModel();

    QString str = QString("SELECT doc.id_doctor, name, mfg, aconst, acd, doc.nom_formula, lens.id "
                          "from lens "
                          "LEFT JOIN doctor_lens doc "
                          "ON (lens.id = doc.id_lens) AND doc.id_doctor=%1;")
                          .arg(id);

    QSqlQuery sql(str);
    sql.exec();

    quint16 numRow=0;
//    qint8 formula;
//    quint8 include;
    quint16 id_lens;
    while(sql.next())
    {
        for(int i=0; i<=5; i++)
        {
            model->setItem(numRow,i,new QStandardItem());
            model->item(numRow,i)->setData(sql.value(i).toString(),Qt::DisplayRole);
        }
//        include = sql.value(5).toUInt();
//        formula = sql.value(5).isNull()?(-1):sql.value(5).toUInt();
        id_lens = sql.value(6).toUInt();
//        model->item(numRow,0)->setData(include, Qt::UserRole);
//        model->item(numRow,0)->setData(formula, Qt::UserRole+1);
        model->item(numRow,0)->setData(id_lens, Qt::UserRole+2);
        numRow++;
    }

//    CCombo_Delegate * pCombo_Delegate = new CCombo_Delegate( ui->tableView );
//    pCombo_Delegate->values().insert( 0, " " );
//    pCombo_Delegate->values().insert( 1, "SRK II" );
//    pCombo_Delegate->values().insert( 2, "SRK T" );
//    pCombo_Delegate->values().insert( 3, "HOFFER Q" );
//    pCombo_Delegate->values().insert( 4, "HOLLADAY" );
//    pCombo_Delegate->values().insert( 5, "HAIGIS" );
//    ui->tableView->setItemDelegateForColumn(5, pCombo_Delegate);

//    CheckBoxDelegate * pCheck_Delegate = new CheckBoxDelegate( ui->tableView );
//    ui->tableView->setItemDelegateForColumn(0, pCheck_Delegate);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    delegate = new CheckBoxDelegate();
//    ui->tableView->setItemDelegate(delegate);
    lst.clear();
    columnPercent << 5 << 20  <<     15 <<            15 <<           15       <<     30;
    lst<<tr("On")<<tr("Lens Name")<<tr("Lens Mfg")<<tr("Mfg A-Const")<<tr("Mfr ACD")<<tr("Primary formula");
    tableWidth = 390;
    for(int i=0; i<lst.count(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
        ui->tableView->setColumnWidth(i, (tableWidth*columnPercent.at(i))/100);
    }

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
//    connect(ui->tableView, SIGNAL(clicked(QModelIndex)),SLOT(changeModel(QModelIndex)));
//    connect(ui->cbInclude, SIGNAL(clicked(bool)), SLOT(include(bool)));
//    connect(ui->radioButton,  SIGNAL(clicked()) , SLOT(selectFormula()));
//    connect(ui->radioButton_2,  SIGNAL(clicked()) , SLOT(selectFormula()));
//    connect(ui->radioButton_3,  SIGNAL(clicked()) , SLOT(selectFormula()));
//    connect(ui->radioButton_4,  SIGNAL(clicked()) , SLOT(selectFormula()));
}

Dialog_Doctor::~Dialog_Doctor()
{
    delete ui;
}

void Dialog_Doctor::saveData()
{
    quint8 formula;
    quint16 id_lens;
    QString str;

    QSqlQuery sql(QString("DELETE FROM doctor_lens WHERE id_doctor=%1;")
                  .arg(curId));
    sql.exec();

    for(quint16 i=0; i<model->rowCount(); i++)
    {
        if(model->data(model->index(i,0)).toInt())
        {
            formula = model->data(model->index(i,5)).toInt();
            id_lens = model->data(model->index(i,0),Qt::UserRole+2).toInt();
            str = QString("INSERT INTO doctor_lens (id_lens, id_doctor, nom_formula) "
                          "VALUES (%1, %2, %3) ;")
                  .arg(id_lens).arg(curId).arg(formula);
            QSqlQuery sql;
            sql.exec(str);
        }
    }
    accept();
}
/*
void dialog_doctor::include(bool val)
{
    quint16  curRow;
    curRow = ui->tableView->currentIndex().row();
    model->setData(model->index(curRow,0), val?1:0, Qt::UserRole);
    changeModel(model->index(curRow,0));
}
*/
/*
void dialog_doctor::changeModel(QModelIndex index)
{
    ui->cbInclude->setChecked(model->data(model->index(index.row(),0),Qt::UserRole).toBool());
    if(ui->cbInclude->isChecked())
    {
        ui->radioButton->setDown(false);
        ui->radioButton_2->setDown(false);
        ui->radioButton_3->setDown(false);
        ui->radioButton_4->setDown(false);
        ui->groupBox->setEnabled(true);
        switch(model->data(model->index(index.row(),0),Qt::UserRole+1).toInt())
        {
        case 0:
            ui->radioButton->setChecked(true);
            break;
        case 1:
            ui->radioButton_2->setChecked(true);
            break;
        case 2:
            ui->radioButton_3->setChecked(true);
            break;
        case 3:
            ui->radioButton_4->setChecked(true);
            break;
        default:
            ui->radioButton->setDown(true);
            ui->radioButton_2->setDown(true);
            ui->radioButton_3->setDown(true);
            ui->radioButton_4->setDown(true);
            break;
        }
    }
    else
        ui->groupBox->setEnabled(false);
}
*/
/*
void dialog_doctor::selectFormula()
{
    quint16  curRow;
    qint8 formula=-1;
    curRow = ui->tableView->currentIndex().row();
    QRadioButton *editor = qobject_cast<QRadioButton *>(sender());
    if(editor == ui->radioButton)
        formula = 0;
    else if(editor == ui->radioButton_2)
        formula = 1;
    else if(editor == ui->radioButton_3)
        formula = 2;
    else if(editor == ui->radioButton_4)
        formula = 3;
    model->setData(model->index(curRow,0), formula, Qt::UserRole+1);
}
*/
