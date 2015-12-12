/********************************************************************************
** Form generated from reading UI file 'dialog_lens.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_LENS_H
#define UI_DIALOG_LENS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Lens
{
public:
    QGridLayout *gridLayout;
    QLineEdit *VALdiam2;
    QLabel *label;
    QLabel *label_7;
    QDialogButtonBox *buttonBox;
    QLineEdit *VALlenght;
    QLineEdit *VALangle;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *VALmfg;
    QLineEdit *VALsf;
    QLabel *label_9;
    QLabel *label_6;
    QLineEdit *VALname;
    QLabel *label_10;
    QLineEdit *VALpower;
    QLabel *label_5;
    QLineEdit *VALacd;
    QLineEdit *VALdiam1;
    QLineEdit *VALaconst;
    QLineEdit *VALloop;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_13;
    QLineEdit *VALpc;
    QLabel *label_11;
    QLineEdit *VALoptic;
    QLabel *label_14;
    QLineEdit *VALnotes;
    QLabel *label_15;
    QLineEdit *VALadded;
    QLabel *label_16;
    QLineEdit *VALhsf;
    QLabel *label_17;
    QLineEdit *VALhacd;
    QLabel *label_18;
    QLineEdit *VALa0;
    QLabel *label_19;
    QLineEdit *VALa1;
    QLabel *label_20;
    QLineEdit *VALa2;

    void setupUi(QDialog *Dialog_Lens)
    {
        if (Dialog_Lens->objectName().isEmpty())
            Dialog_Lens->setObjectName(QStringLiteral("Dialog_Lens"));
        Dialog_Lens->resize(330, 303);
        gridLayout = new QGridLayout(Dialog_Lens);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        VALdiam2 = new QLineEdit(Dialog_Lens);
        VALdiam2->setObjectName(QStringLiteral("VALdiam2"));

        gridLayout->addWidget(VALdiam2, 3, 1, 1, 1);

        label = new QLabel(Dialog_Lens);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_7 = new QLabel(Dialog_Lens);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog_Lens);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 23, 0, 1, 2);

        VALlenght = new QLineEdit(Dialog_Lens);
        VALlenght->setObjectName(QStringLiteral("VALlenght"));

        gridLayout->addWidget(VALlenght, 4, 1, 1, 1);

        VALangle = new QLineEdit(Dialog_Lens);
        VALangle->setObjectName(QStringLiteral("VALangle"));

        gridLayout->addWidget(VALangle, 5, 1, 1, 1);

        label_8 = new QLabel(Dialog_Lens);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        label_3 = new QLabel(Dialog_Lens);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(Dialog_Lens);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        VALmfg = new QLineEdit(Dialog_Lens);
        VALmfg->setObjectName(QStringLiteral("VALmfg"));

        gridLayout->addWidget(VALmfg, 1, 1, 1, 1);

        VALsf = new QLineEdit(Dialog_Lens);
        VALsf->setObjectName(QStringLiteral("VALsf"));

        gridLayout->addWidget(VALsf, 8, 1, 1, 1);

        label_9 = new QLabel(Dialog_Lens);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        label_6 = new QLabel(Dialog_Lens);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        VALname = new QLineEdit(Dialog_Lens);
        VALname->setObjectName(QStringLiteral("VALname"));

        gridLayout->addWidget(VALname, 0, 1, 1, 1);

        label_10 = new QLabel(Dialog_Lens);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

        VALpower = new QLineEdit(Dialog_Lens);
        VALpower->setObjectName(QStringLiteral("VALpower"));

        gridLayout->addWidget(VALpower, 9, 1, 1, 1);

        label_5 = new QLabel(Dialog_Lens);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        VALacd = new QLineEdit(Dialog_Lens);
        VALacd->setObjectName(QStringLiteral("VALacd"));

        gridLayout->addWidget(VALacd, 7, 1, 1, 1);

        VALdiam1 = new QLineEdit(Dialog_Lens);
        VALdiam1->setObjectName(QStringLiteral("VALdiam1"));

        gridLayout->addWidget(VALdiam1, 2, 1, 1, 1);

        VALaconst = new QLineEdit(Dialog_Lens);
        VALaconst->setObjectName(QStringLiteral("VALaconst"));

        gridLayout->addWidget(VALaconst, 6, 1, 1, 1);

        VALloop = new QLineEdit(Dialog_Lens);
        VALloop->setObjectName(QStringLiteral("VALloop"));

        gridLayout->addWidget(VALloop, 1, 3, 1, 1);

        label_12 = new QLabel(Dialog_Lens);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 1, 2, 1, 1);

        label_4 = new QLabel(Dialog_Lens);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_13 = new QLabel(Dialog_Lens);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 2, 2, 1, 1);

        VALpc = new QLineEdit(Dialog_Lens);
        VALpc->setObjectName(QStringLiteral("VALpc"));

        gridLayout->addWidget(VALpc, 2, 3, 1, 1);

        label_11 = new QLabel(Dialog_Lens);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 0, 2, 1, 1);

        VALoptic = new QLineEdit(Dialog_Lens);
        VALoptic->setObjectName(QStringLiteral("VALoptic"));

        gridLayout->addWidget(VALoptic, 0, 3, 1, 1);

        label_14 = new QLabel(Dialog_Lens);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 3, 2, 1, 1);

        VALnotes = new QLineEdit(Dialog_Lens);
        VALnotes->setObjectName(QStringLiteral("VALnotes"));

        gridLayout->addWidget(VALnotes, 3, 3, 1, 1);

        label_15 = new QLabel(Dialog_Lens);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 4, 2, 1, 1);

        VALadded = new QLineEdit(Dialog_Lens);
        VALadded->setObjectName(QStringLiteral("VALadded"));

        gridLayout->addWidget(VALadded, 4, 3, 1, 1);

        label_16 = new QLabel(Dialog_Lens);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 5, 2, 1, 1);

        VALhsf = new QLineEdit(Dialog_Lens);
        VALhsf->setObjectName(QStringLiteral("VALhsf"));

        gridLayout->addWidget(VALhsf, 5, 3, 1, 1);

        label_17 = new QLabel(Dialog_Lens);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 6, 2, 1, 1);

        VALhacd = new QLineEdit(Dialog_Lens);
        VALhacd->setObjectName(QStringLiteral("VALhacd"));

        gridLayout->addWidget(VALhacd, 6, 3, 1, 1);

        label_18 = new QLabel(Dialog_Lens);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 7, 2, 1, 1);

        VALa0 = new QLineEdit(Dialog_Lens);
        VALa0->setObjectName(QStringLiteral("VALa0"));

        gridLayout->addWidget(VALa0, 7, 3, 1, 1);

        label_19 = new QLabel(Dialog_Lens);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 8, 2, 1, 1);

        VALa1 = new QLineEdit(Dialog_Lens);
        VALa1->setObjectName(QStringLiteral("VALa1"));

        gridLayout->addWidget(VALa1, 8, 3, 1, 1);

        label_20 = new QLabel(Dialog_Lens);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 9, 2, 1, 1);

        VALa2 = new QLineEdit(Dialog_Lens);
        VALa2->setObjectName(QStringLiteral("VALa2"));

        gridLayout->addWidget(VALa2, 9, 3, 1, 1);


        retranslateUi(Dialog_Lens);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_Lens, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_Lens, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_Lens);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Lens)
    {
        Dialog_Lens->setWindowTitle(QApplication::translate("Dialog_Lens", "Dialog", 0));
        label->setText(QApplication::translate("Dialog_Lens", "Lens Name", 0));
        label_7->setText(QApplication::translate("Dialog_Lens", "Mfg A-Const", 0));
        label_8->setText(QApplication::translate("Dialog_Lens", "Mfg ACD", 0));
        label_3->setText(QApplication::translate("Dialog_Lens", "Optic Diametr 1", 0));
        label_2->setText(QApplication::translate("Dialog_Lens", "Lens Mfg", 0));
        label_9->setText(QApplication::translate("Dialog_Lens", "Mfg SF", 0));
        label_6->setText(QApplication::translate("Dialog_Lens", "Loop Angle", 0));
        label_10->setText(QApplication::translate("Dialog_Lens", "Power Range", 0));
        label_5->setText(QApplication::translate("Dialog_Lens", "Over Lenght", 0));
        label_12->setText(QApplication::translate("Dialog_Lens", "Loop Material", 0));
        label_4->setText(QApplication::translate("Dialog_Lens", "Optic Diametr 2", 0));
        label_13->setText(QApplication::translate("Dialog_Lens", "PC", 0));
        label_11->setText(QApplication::translate("Dialog_Lens", "Optic Material", 0));
        label_14->setText(QApplication::translate("Dialog_Lens", "Notes", 0));
        label_15->setText(QApplication::translate("Dialog_Lens", "Added", 0));
        label_16->setText(QApplication::translate("Dialog_Lens", "Holladay SF", 0));
        label_17->setText(QApplication::translate("Dialog_Lens", "Holladay ACD", 0));
        label_18->setText(QApplication::translate("Dialog_Lens", "A0", 0));
        label_19->setText(QApplication::translate("Dialog_Lens", "A1", 0));
        label_20->setText(QApplication::translate("Dialog_Lens", "A2", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Lens: public Ui_Dialog_Lens {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_LENS_H
