/********************************************************************************
** Form generated from reading UI file 'dialog_doctor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DOCTOR_H
#define UI_DIALOG_DOCTOR_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Doctor
{
public:
    QGridLayout *gridLayout;
    QLineEdit *VALlast;
    QLineEdit *VALid;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *VALnote;
    QTableView *tableView;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *VALname;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_Doctor)
    {
        if (Dialog_Doctor->objectName().isEmpty())
            Dialog_Doctor->setObjectName(QStringLiteral("Dialog_Doctor"));
        Dialog_Doctor->resize(435, 445);
        gridLayout = new QGridLayout(Dialog_Doctor);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        VALlast = new QLineEdit(Dialog_Doctor);
        VALlast->setObjectName(QStringLiteral("VALlast"));

        gridLayout->addWidget(VALlast, 2, 1, 1, 2);

        VALid = new QLineEdit(Dialog_Doctor);
        VALid->setObjectName(QStringLiteral("VALid"));
        VALid->setEnabled(false);
        VALid->setReadOnly(true);

        gridLayout->addWidget(VALid, 0, 1, 1, 1);

        label_3 = new QLabel(Dialog_Doctor);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(Dialog_Doctor);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        VALnote = new QLineEdit(Dialog_Doctor);
        VALnote->setObjectName(QStringLiteral("VALnote"));

        gridLayout->addWidget(VALnote, 3, 1, 1, 2);

        tableView = new QTableView(Dialog_Doctor);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->horizontalHeader()->setHighlightSections(false);
        tableView->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(tableView, 5, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label = new QLabel(Dialog_Doctor);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(Dialog_Doctor);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        VALname = new QLineEdit(Dialog_Doctor);
        VALname->setObjectName(QStringLiteral("VALname"));

        gridLayout->addWidget(VALname, 1, 1, 1, 2);

        buttonBox = new QDialogButtonBox(Dialog_Doctor);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 6, 2, 1, 1);


        retranslateUi(Dialog_Doctor);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_Doctor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_Doctor, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_Doctor);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Doctor)
    {
        Dialog_Doctor->setWindowTitle(QApplication::translate("Dialog_Doctor", "Dialog", 0));
        label_3->setText(QApplication::translate("Dialog_Doctor", "First Name", 0));
        label_2->setText(QApplication::translate("Dialog_Doctor", "Note", 0));
        label->setText(QApplication::translate("Dialog_Doctor", "Doctor ID", 0));
        label_4->setText(QApplication::translate("Dialog_Doctor", "Last Name", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Doctor: public Ui_Dialog_Doctor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DOCTOR_H
