/********************************************************************************
** Form generated from reading UI file 'bigviewnumcur.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIGVIEWNUMCUR_H
#define UI_BIGVIEWNUMCUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Bigviewnumcur
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *lVIT;
    QLabel *lCurACD;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lCurAL;
    QLabel *lLT;
    QLabel *lCurVIT;
    QLabel *lCurLT;
    QLabel *label_3;
    QLineEdit *leData;
    QLabel *label_5;
    QLabel *lAL;
    QLineEdit *lFioDoctor;
    QLineEdit *lFioPatient;
    QLabel *lACD;
    QLabel *label_6;
    QLineEdit *leSide;
    QLabel *lData;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *Bigviewnumcur)
    {
        if (Bigviewnumcur->objectName().isEmpty())
            Bigviewnumcur->setObjectName(QStringLiteral("Bigviewnumcur"));
        Bigviewnumcur->resize(590, 77);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Bigviewnumcur->sizePolicy().hasHeightForWidth());
        Bigviewnumcur->setSizePolicy(sizePolicy);
        Bigviewnumcur->setMinimumSize(QSize(0, 0));
        Bigviewnumcur->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        gridLayout_2 = new QGridLayout(Bigviewnumcur);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        lVIT = new QLabel(Bigviewnumcur);
        lVIT->setObjectName(QStringLiteral("lVIT"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        lVIT->setFont(font);
        lVIT->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lVIT->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lVIT, 2, 8, 1, 1);

        lCurACD = new QLabel(Bigviewnumcur);
        lCurACD->setObjectName(QStringLiteral("lCurACD"));
        lCurACD->setFont(font);
        lCurACD->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(lCurACD, 0, 9, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        lCurAL = new QLabel(Bigviewnumcur);
        lCurAL->setObjectName(QStringLiteral("lCurAL"));
        QFont font1;
        font1.setPointSize(36);
        font1.setBold(true);
        font1.setWeight(75);
        font1.setStyleStrategy(QFont::PreferAntialias);
        lCurAL->setFont(font1);
        lCurAL->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lCurAL->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lCurAL, 0, 6, 3, 2);

        lLT = new QLabel(Bigviewnumcur);
        lLT->setObjectName(QStringLiteral("lLT"));
        lLT->setFont(font);
        lLT->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lLT->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lLT, 1, 8, 1, 1);

        lCurVIT = new QLabel(Bigviewnumcur);
        lCurVIT->setObjectName(QStringLiteral("lCurVIT"));
        lCurVIT->setFont(font);
        lCurVIT->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(lCurVIT, 2, 9, 1, 1);

        lCurLT = new QLabel(Bigviewnumcur);
        lCurLT->setObjectName(QStringLiteral("lCurLT"));
        lCurLT->setFont(font);
        lCurLT->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(lCurLT, 1, 9, 1, 1);

        label_3 = new QLabel(Bigviewnumcur);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 5, 1, 1);

        leData = new QLineEdit(Bigviewnumcur);
        leData->setObjectName(QStringLiteral("leData"));
        leData->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leData->sizePolicy().hasHeightForWidth());
        leData->setSizePolicy(sizePolicy1);
        leData->setMinimumSize(QSize(0, 0));
        leData->setMaximumSize(QSize(380, 16777215));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        font3.setKerning(false);
        font3.setStyleStrategy(QFont::PreferAntialias);
        leData->setFont(font3);
        leData->setAutoFillBackground(false);
        leData->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        leData->setInputMask(QStringLiteral(""));
        leData->setText(QStringLiteral(""));
        leData->setFrame(false);
        leData->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        leData->setReadOnly(true);
        leData->setPlaceholderText(QStringLiteral(""));

        gridLayout->addWidget(leData, 0, 1, 1, 1);

        label_5 = new QLabel(Bigviewnumcur);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        lAL = new QLabel(Bigviewnumcur);
        lAL->setObjectName(QStringLiteral("lAL"));
        lAL->setFont(font);
        lAL->setLayoutDirection(Qt::LeftToRight);
        lAL->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lAL->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lAL, 2, 5, 1, 1);

        lFioDoctor = new QLineEdit(Bigviewnumcur);
        lFioDoctor->setObjectName(QStringLiteral("lFioDoctor"));
        lFioDoctor->setEnabled(false);
        sizePolicy1.setHeightForWidth(lFioDoctor->sizePolicy().hasHeightForWidth());
        lFioDoctor->setSizePolicy(sizePolicy1);
        lFioDoctor->setMinimumSize(QSize(0, 0));
        lFioDoctor->setMaximumSize(QSize(380, 16777215));
        lFioDoctor->setFont(font3);
        lFioDoctor->setAutoFillBackground(false);
        lFioDoctor->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lFioDoctor->setInputMask(QStringLiteral(""));
        lFioDoctor->setText(QStringLiteral("Select doctor"));
        lFioDoctor->setFrame(false);
        lFioDoctor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lFioDoctor->setReadOnly(true);
        lFioDoctor->setPlaceholderText(QStringLiteral(""));

        gridLayout->addWidget(lFioDoctor, 2, 1, 1, 1);

        lFioPatient = new QLineEdit(Bigviewnumcur);
        lFioPatient->setObjectName(QStringLiteral("lFioPatient"));
        lFioPatient->setEnabled(false);
        sizePolicy1.setHeightForWidth(lFioPatient->sizePolicy().hasHeightForWidth());
        lFioPatient->setSizePolicy(sizePolicy1);
        lFioPatient->setMinimumSize(QSize(0, 0));
        lFioPatient->setMaximumSize(QSize(380, 16777215));
        lFioPatient->setFont(font3);
        lFioPatient->setAutoFillBackground(false);
        lFioPatient->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lFioPatient->setInputMask(QStringLiteral(""));
        lFioPatient->setText(QStringLiteral("Select patient"));
        lFioPatient->setFrame(false);
        lFioPatient->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lFioPatient->setReadOnly(true);
        lFioPatient->setPlaceholderText(QStringLiteral(""));

        gridLayout->addWidget(lFioPatient, 1, 1, 1, 1);

        lACD = new QLabel(Bigviewnumcur);
        lACD->setObjectName(QStringLiteral("lACD"));
        lACD->setFont(font);
        lACD->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lACD->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lACD, 0, 8, 1, 1);

        label_6 = new QLabel(Bigviewnumcur);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        leSide = new QLineEdit(Bigviewnumcur);
        leSide->setObjectName(QStringLiteral("leSide"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leSide->sizePolicy().hasHeightForWidth());
        leSide->setSizePolicy(sizePolicy2);
        leSide->setMaximumSize(QSize(80, 16777215));
        leSide->setFont(font1);
        leSide->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        leSide->setFrame(false);
        leSide->setAlignment(Qt::AlignCenter);
        leSide->setReadOnly(true);

        gridLayout->addWidget(leSide, 0, 3, 3, 1);

        lData = new QLabel(Bigviewnumcur);
        lData->setObjectName(QStringLiteral("lData"));
        lData->setFont(font);
        lData->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(lData, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 4, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(Bigviewnumcur);

        QMetaObject::connectSlotsByName(Bigviewnumcur);
    } // setupUi

    void retranslateUi(QWidget *Bigviewnumcur)
    {
        Bigviewnumcur->setWindowTitle(QApplication::translate("Bigviewnumcur", "Form", 0));
        lVIT->setText(QApplication::translate("Bigviewnumcur", "VIT", 0));
        lCurACD->setText(QApplication::translate("Bigviewnumcur", "00.00", 0));
        lCurAL->setText(QApplication::translate("Bigviewnumcur", "00.00", 0));
        lLT->setText(QApplication::translate("Bigviewnumcur", "LT", 0));
        lCurVIT->setText(QApplication::translate("Bigviewnumcur", "00.00", 0));
        lCurLT->setText(QApplication::translate("Bigviewnumcur", "00.00", 0));
        label_3->setText(QString());
        label_5->setText(QApplication::translate("Bigviewnumcur", "Patient:", 0));
        lAL->setText(QApplication::translate("Bigviewnumcur", "AL", 0));
        lACD->setText(QApplication::translate("Bigviewnumcur", "ACD", 0));
        label_6->setText(QApplication::translate("Bigviewnumcur", "Doctor:", 0));
        leSide->setText(QApplication::translate("Bigviewnumcur", "OD", 0));
        lData->setText(QApplication::translate("Bigviewnumcur", "Data:", 0));
    } // retranslateUi

};

namespace Ui {
    class Bigviewnumcur: public Ui_Bigviewnumcur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIGVIEWNUMCUR_H
