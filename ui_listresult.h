/********************************************************************************
** Form generated from reading UI file 'listresult.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTRESULT_H
#define UI_LISTRESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ListResult
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ListResult)
    {
        if (ListResult->objectName().isEmpty())
            ListResult->setObjectName(QStringLiteral("ListResult"));
        ListResult->resize(400, 300);
        gridLayout_2 = new QGridLayout(ListResult);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ListResult);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ListResult);
        QObject::connect(buttonBox, SIGNAL(accepted()), ListResult, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ListResult, SLOT(reject()));

        QMetaObject::connectSlotsByName(ListResult);
    } // setupUi

    void retranslateUi(QDialog *ListResult)
    {
        ListResult->setWindowTitle(QApplication::translate("ListResult", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ListResult: public Ui_ListResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTRESULT_H
