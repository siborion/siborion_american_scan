/********************************************************************************
** Form generated from reading UI file 'bigviewnum.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIGVIEWNUM_H
#define UI_BIGVIEWNUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bigviewnum
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QLabel *lDevAL_2;
    QLabel *lAveVIT;
    QLabel *lStdAL;
    QLabel *lDevAcd_2;
    QLabel *lAveLT;
    QLabel *label_13;
    QLabel *lAveAL;
    QLabel *lStdLT;
    QLabel *lDevVit_2;
    QLabel *lAveACD;
    QFrame *line_5;
    QLabel *lStdVIT;
    QLabel *lAvgLt_2;
    QLabel *label_5;
    QLabel *lAvgVit_2;
    QLabel *lAvgAL_2;
    QLabel *lAvgAcd_2;
    QLabel *lStdACD;
    QLabel *lDevLt_2;

    void setupUi(QWidget *bigviewnum)
    {
        if (bigviewnum->objectName().isEmpty())
            bigviewnum->setObjectName(QStringLiteral("bigviewnum"));
        bigviewnum->resize(225, 167);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bigviewnum->sizePolicy().hasHeightForWidth());
        bigviewnum->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(bigviewnum);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(bigviewnum);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(5);
        gridLayout_4->setVerticalSpacing(2);
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        lDevAL_2 = new QLabel(frame);
        lDevAL_2->setObjectName(QStringLiteral("lDevAL_2"));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        lDevAL_2->setFont(font);
        lDevAL_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(lDevAL_2, 6, 1, 3, 1);

        lAveVIT = new QLabel(frame);
        lAveVIT->setObjectName(QStringLiteral("lAveVIT"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lAveVIT->setFont(font1);
        lAveVIT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lAveVIT, 3, 2, 1, 1);

        lStdAL = new QLabel(frame);
        lStdAL->setObjectName(QStringLiteral("lStdAL"));
        lStdAL->setFont(font1);
        lStdAL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lStdAL, 8, 0, 1, 1);

        lDevAcd_2 = new QLabel(frame);
        lDevAcd_2->setObjectName(QStringLiteral("lDevAcd_2"));
        lDevAcd_2->setFont(font1);

        gridLayout_4->addWidget(lDevAcd_2, 6, 3, 1, 1);

        lAveLT = new QLabel(frame);
        lAveLT->setObjectName(QStringLiteral("lAveLT"));
        lAveLT->setFont(font1);
        lAveLT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lAveLT, 2, 2, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font1);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_13, 5, 0, 1, 4);

        lAveAL = new QLabel(frame);
        lAveAL->setObjectName(QStringLiteral("lAveAL"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        lAveAL->setFont(font2);
        lAveAL->setLayoutDirection(Qt::LeftToRight);
        lAveAL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lAveAL, 3, 0, 1, 1);

        lStdLT = new QLabel(frame);
        lStdLT->setObjectName(QStringLiteral("lStdLT"));
        lStdLT->setFont(font1);
        lStdLT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lStdLT, 7, 2, 1, 1);

        lDevVit_2 = new QLabel(frame);
        lDevVit_2->setObjectName(QStringLiteral("lDevVit_2"));
        lDevVit_2->setFont(font1);

        gridLayout_4->addWidget(lDevVit_2, 8, 3, 1, 1);

        lAveACD = new QLabel(frame);
        lAveACD->setObjectName(QStringLiteral("lAveACD"));
        lAveACD->setFont(font1);
        lAveACD->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lAveACD, 1, 2, 1, 1);

        line_5 = new QFrame(frame);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_5, 4, 0, 1, 4);

        lStdVIT = new QLabel(frame);
        lStdVIT->setObjectName(QStringLiteral("lStdVIT"));
        lStdVIT->setFont(font1);
        lStdVIT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lStdVIT, 8, 2, 1, 1);

        lAvgLt_2 = new QLabel(frame);
        lAvgLt_2->setObjectName(QStringLiteral("lAvgLt_2"));
        lAvgLt_2->setFont(font1);

        gridLayout_4->addWidget(lAvgLt_2, 2, 3, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_5, 0, 0, 1, 4);

        lAvgVit_2 = new QLabel(frame);
        lAvgVit_2->setObjectName(QStringLiteral("lAvgVit_2"));
        lAvgVit_2->setFont(font1);

        gridLayout_4->addWidget(lAvgVit_2, 3, 3, 1, 1);

        lAvgAL_2 = new QLabel(frame);
        lAvgAL_2->setObjectName(QStringLiteral("lAvgAL_2"));
        lAvgAL_2->setFont(font);
        lAvgAL_2->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(lAvgAL_2, 1, 1, 3, 1);

        lAvgAcd_2 = new QLabel(frame);
        lAvgAcd_2->setObjectName(QStringLiteral("lAvgAcd_2"));
        lAvgAcd_2->setFont(font1);

        gridLayout_4->addWidget(lAvgAcd_2, 1, 3, 1, 1);

        lStdACD = new QLabel(frame);
        lStdACD->setObjectName(QStringLiteral("lStdACD"));
        lStdACD->setFont(font2);
        lStdACD->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(lStdACD, 6, 2, 1, 1);

        lDevLt_2 = new QLabel(frame);
        lDevLt_2->setObjectName(QStringLiteral("lDevLt_2"));
        lDevLt_2->setFont(font1);

        gridLayout_4->addWidget(lDevLt_2, 7, 3, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(bigviewnum);

        QMetaObject::connectSlotsByName(bigviewnum);
    } // setupUi

    void retranslateUi(QWidget *bigviewnum)
    {
        bigviewnum->setWindowTitle(QApplication::translate("bigviewnum", "Form", 0));
        lDevAL_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
        lAveVIT->setText(QApplication::translate("bigviewnum", "VIT", 0));
        lStdAL->setText(QApplication::translate("bigviewnum", "AL", 0));
        lDevAcd_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
        lAveLT->setText(QApplication::translate("bigviewnum", "LT", 0));
        label_13->setText(QApplication::translate("bigviewnum", "Std. deviation", 0));
        lAveAL->setText(QApplication::translate("bigviewnum", "AL", 0));
        lStdLT->setText(QApplication::translate("bigviewnum", "LT", 0));
        lDevVit_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
        lAveACD->setText(QApplication::translate("bigviewnum", "ACD", 0));
        lStdVIT->setText(QApplication::translate("bigviewnum", "VIT", 0));
        lAvgLt_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
        label_5->setText(QApplication::translate("bigviewnum", "Average", 0));
        lAvgVit_2->setText(QApplication::translate("bigviewnum", "00.00", 0));
        lAvgAL_2->setText(QApplication::translate("bigviewnum", "00.00", 0));
        lAvgAcd_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
        lStdACD->setText(QApplication::translate("bigviewnum", "ACD", 0));
        lDevLt_2->setText(QApplication::translate("bigviewnum", "0.00", 0));
    } // retranslateUi

};

namespace Ui {
    class bigviewnum: public Ui_bigviewnum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIGVIEWNUM_H
