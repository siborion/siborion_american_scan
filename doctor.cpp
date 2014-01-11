#include "doctor.h"

doctor::doctor(QWidget *parent) :
    QDialog(parent)
{
    setMinimumWidth(350);

    QList<int> columnPercent;
    QStringList lst;

    QVBoxLayout *layout        = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout  = new QHBoxLayout();
//----------------------------------------------------------------
    modelDoctor = new QStandardItemModel();
    modelDoctor->setRowCount(4);
    modelDoctor->setColumnCount(2);
    twDoctor = new adjview();
    twDoctor->setModel(modelDoctor);
    twDoctor->verticalHeader()->hide();
    twDoctor->horizontalHeader()->hide();
    twDoctor->setMaximumHeight(120);
    twDoctor->setMinimumHeight(120);
    twDoctor->setFrameShape(QFrame::NoFrame);
    twDoctor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twDoctor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    columnPercent.clear();
    columnPercent<<50<<50;
    twDoctor->setColumnPercent(columnPercent);

    for(quint8 i=0; i<4; i++)
    {
        modelDoctor->setItem(i, 0, new QStandardItem(baseMap[i][0]));
        modelDoctor->item   (i, 0)->setBackground(Qt::lightGray);
        modelDoctor->item   (i, 0)->setEditable(false);
    }
    //----------------------------------------------------------------
    QGroupBox   *gbFormula     = new QGroupBox("Primary Formula");
    QGridLayout *formulaLayout = new QGridLayout(gbFormula);
    QCheckBox   *cbSrk2          = new QCheckBox(tr("SRK II"));
    QCheckBox   *cbHofferQ       = new QCheckBox(tr("HOFFER Q"));
    QCheckBox   *cbSrkT          = new QCheckBox(tr("SRK T"));
    QCheckBox   *cbHolladay      = new QCheckBox(tr("HOLLADAY"));
    formulaLayout->addWidget(cbSrk2,    0, 0);
    formulaLayout->addWidget(cbHofferQ, 0, 1);
    formulaLayout->addWidget(cbSrkT,    1, 0);
    formulaLayout->addWidget(cbHolladay,1, 1);
//----------------------------------------------------------------
    twLens = new adjview();
    modelLens = new QStandardItemModel();
    modelLens->setColumnCount(4);
    modelLens->setRowCount(1);
    lst.clear();
    lst<<tr("Lens Name")<<tr("Lens Mfg")<<tr("Mfg A-Const")<<tr("Mfr ACD");
    modelLens->setHorizontalHeaderLabels(lst);
    twLens->setModel(modelLens);
    twLens->verticalHeader()->hide();
    twLens->setMaximumHeight(120);
    twLens->setMinimumHeight(120);
    twLens->setFrameShape(QFrame::NoFrame);
    twLens->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    twLens->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    columnPercent.clear();
    columnPercent<<25<<25<<25<<25;
    twLens->setColumnPercent(columnPercent);
//-----------------------------------------------------------------

    layout->addWidget(twDoctor);
    layout->addWidget(gbFormula);
    layout->addWidget(twLens);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    QPushButton *pbOk = new QPushButton(tr("Ok"));

    buttonLayout->addWidget(pbCancel);
    buttonLayout->addWidget(pbOk);

    layout->addLayout(buttonLayout);

    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
}
