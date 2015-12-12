/********************************************************************************
** Form generated from reading UI file 'velosity.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VELOSITY_H
#define UI_VELOSITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Velosity
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Velosity)
    {
        if (Velosity->objectName().isEmpty())
            Velosity->setObjectName(QStringLiteral("Velosity"));
        Velosity->resize(244, 71);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Velosity->sizePolicy().hasHeightForWidth());
        Velosity->setSizePolicy(sizePolicy);
        Velosity->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(Velosity);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(Velosity);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 1, 5, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        gridLayout_2->addWidget(label_8, 1, 6, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 1, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 0, 5, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout_2->addWidget(label_7, 0, 6, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(Velosity);

        QMetaObject::connectSlotsByName(Velosity);
    } // setupUi

    void retranslateUi(QWidget *Velosity)
    {
        Velosity->setWindowTitle(QApplication::translate("Velosity", "Form", 0));
        label_6->setText(QApplication::translate("Velosity", "VIT:", 0));
        label_8->setText(QApplication::translate("Velosity", "1532 \320\274/s", 0));
        label_4->setText(QApplication::translate("Velosity", "1534 \320\274/s", 0));
        label_2->setText(QApplication::translate("Velosity", "ACD:", 0));
        label_3->setText(QApplication::translate("Velosity", "1555 \320\274/s", 0));
        label->setText(QApplication::translate("Velosity", "Ave.:", 0));
        label_5->setText(QApplication::translate("Velosity", "LT:", 0));
        label_7->setText(QApplication::translate("Velosity", "1641 \320\274/s", 0));
    } // retranslateUi

};

namespace Ui {
    class Velosity: public Ui_Velosity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VELOSITY_H
