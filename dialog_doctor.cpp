#include "dialog_doctor.h"
#include "ui_dialog_doctor.h"

dialog_doctor::dialog_doctor(quint32 id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_doctor)
{
    QString str;
    QList<int> columnPercent;
    QStringList lst;
    quint16 tableWidth;

    ui->setupUi(this);
    pBase = scanbase::instanse();
    pBaseFill = new basefill(id, children(), (QString)"doctor");
    pBaseFill->fillData();

    model = new QSqlQueryModel();
    ui->tableView->setModel(model);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    lst.clear();
    columnPercent<< 20 << 20  <<           20 <<              20 <<          20 << 0;
    lst<<tr("V")<<tr("Lens Name")<<tr("Lens Mfg")<<tr("Mfg A-Const")<<tr("Mfr ACD")<<" ";
    str = "SELECT * from v_doctor_dialog;";
    model->setQuery(str);
    tableWidth = 300;
    for(int i=0; i<lst.count(); i++)
    {
        model->setHeaderData(i, Qt::Horizontal, lst.at(i), Qt::DisplayRole);
        ui->tableView->setColumnWidth(i, (tableWidth*columnPercent.at(i))/100);
    }
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveData()));
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
