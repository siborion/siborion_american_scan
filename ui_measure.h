/********************************************************************************
** Form generated from reading UI file 'measure.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURE_H
#define UI_MEASURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Measure
{
public:

    void setupUi(QWidget *Measure)
    {
        if (Measure->objectName().isEmpty())
            Measure->setObjectName(QStringLiteral("Measure"));
        Measure->resize(400, 300);

        retranslateUi(Measure);

        QMetaObject::connectSlotsByName(Measure);
    } // setupUi

    void retranslateUi(QWidget *Measure)
    {
        Measure->setWindowTitle(QApplication::translate("Measure", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Measure: public Ui_Measure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_H
