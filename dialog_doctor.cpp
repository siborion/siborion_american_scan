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
    model->setRowCount(4);
    model->setColumnCount(4);
//    model->setTable("lens");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();
//    qDebug()<<"0000000000";
//    qDebug()<<model->lastError().text();
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    delegate = new CheckBoxDelegate();
    ui->tableView->setItemDelegate(delegate);
    lst.clear();
    columnPercent<< 0 << 25  <<           25 <<              25 <<          25 << 0;
    lst<<tr("V")<<tr("Lens Name")<<tr("Lens Mfg")<<tr("Mfg A-Const")<<tr("Mfr ACD")<<" ";
    tableWidth = 300;
    for(int i=0; i<lst.count(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
        ui->tableView->setColumnWidth(i, (tableWidth*columnPercent.at(i))/100);
    }

    model->setData(model->index(1,1), 8, Qt::DisplayRole);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
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
//    qDebug()<<model->data(model->index(ui->tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();
//    model->setData(model->index(ui->tableView->currentIndex().row(),0), val?1:0, Qt::DisplayRole);
    model->setData(model->index(0,0), 8, Qt::DisplayRole);
}
