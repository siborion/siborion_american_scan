/********************************************************************************
** Form generated from reading UI file 'dialogserial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSERIAL_H
#define UI_DIALOGSERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogSerial
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSerial)
    {
        if (DialogSerial->objectName().isEmpty())
            DialogSerial->setObjectName(QStringLiteral("DialogSerial"));
        DialogSerial->resize(366, 80);
        buttonBox = new QDialogButtonBox(DialogSerial);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 30, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(DialogSerial);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSerial, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSerial, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSerial);
    } // setupUi

    void retranslateUi(QDialog *DialogSerial)
    {
        DialogSerial->setWindowTitle(QApplication::translate("DialogSerial", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSerial: public Ui_DialogSerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSERIAL_H
