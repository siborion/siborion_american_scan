#include "dialog_doctor.h"
#include "ui_dialog_doctor.h"

dialog_doctor::dialog_doctor(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_doctor)
{
    QList<int> columnPercent;
    QStringList lst;
    quint16 tableWidth;

    pBase = scanbase::instanse();

    ui->setupUi(this);
    pBase = scanbase::instanse();
    pBaseFill = new basefill(id, children(), (QString)"doctor");
    pBaseFill->fillData();

    model = new QStandardItemModel();
    QSqlQuery sql(QString("SELECT name, mfg, aconst, acd, doc.id_doctor, doc.nom_formula "
    "from lens "
    "LEFT JOIN doctor_lens doc "
    "ON (lens.id = doc.id_lens) AND doc.id_doctor=%1;")
    .arg(id));
    sql.exec();

    quint16 numRow=0;
    qint8 formula;
    quint8 include;
    while(sql.next())
    {
        for(int i=0; i<=3; i++)
        {
            model->setItem(numRow,i,new QStandardItem());
            model->item(numRow,i)->setData(sql.value(i).toString(),Qt::DisplayRole);
        }
        include = sql.value(4).toUInt();
        formula = sql.value(5).isNull()?(-1):sql.value(5).toUInt();
        qDebug()<<formula;
        model->item(numRow,0)->setData(include, Qt::UserRole);
        model->item(numRow,0)->setData(formula, Qt::UserRole+1);
        numRow++;
    }

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    delegate = new CheckBoxDelegate();
    ui->tableView->setItemDelegate(delegate);
    lst.clear();
    columnPercent << 25  <<           25 <<              25 <<       25;
    lst<<tr("Lens Name")<<tr("Lens Mfg")<<tr("Mfg A-Const")<<tr("Mfr ACD");
    tableWidth = 300;
    for(int i=0; i<lst.count(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
        ui->tableView->setColumnWidth(i, (tableWidth*columnPercent.at(i))/100);
    }

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)),SLOT(changeModel(QModelIndex)));
    connect(ui->cbInclude, SIGNAL(clicked(bool)), SLOT(include(bool)));
}

dialog_doctor::~dialog_doctor()
{
    delete ui;
}

void dialog_doctor::saveData()
{
    pBaseFill->saveData();
    accept();
}

void dialog_doctor::include(bool val)
{
    quint16  curRow;
    curRow = ui->tableView->currentIndex().row();
    model->setData(model->index(curRow,0), val?1:0, Qt::UserRole);
    changeModel(model->index(curRow,0));
}

void dialog_doctor::changeModel(QModelIndex index)
{
    ui->cbInclude->setChecked(model->data(model->index(index.row(),0),Qt::UserRole).toBool());
    if(ui->cbInclude->isChecked())
    {
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
            qDebug()<<"555555555555";
            ui->radioButton->setChecked(false);
            ui->radioButton_2->setChecked(false);
            ui->radioButton_3->setChecked(false);
            ui->radioButton_4->setChecked(false);
            break;
        }
    }
    else
        ui->groupBox->setEnabled(false);
}

