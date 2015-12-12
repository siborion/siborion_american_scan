/********************************************************************************
** Form generated from reading UI file 'calculator_patient.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_PATIENT_H
#define UI_CALCULATOR_PATIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <leaddzero.h>

QT_BEGIN_NAMESPACE

class Ui_calculator_patient
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLabel *label_12;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_11;
    leAddZero *leK1;
    QLabel *label_6;
    leAddZero *leK2;
    QFrame *line;
    leAddZero *leK;
    QGridLayout *gridLayout_5;
    leAddZero *leAL_measure;
    QLineEdit *leACD_measure;
    QLabel *label_9;
    QLabel *label_13;
    QPushButton *pbSide;
    QLabel *label_4;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QLabel *label_17;
    QLineEdit *leACD_personal;
    QLineEdit *leRx_personal;
    QLineEdit *leSF_personal;
    QLabel *label_15;
    QLabel *label_14;
    QLineEdit *leAConst_personal;
    QLabel *label_16;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lePatientId;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lePatientName;
    QLineEdit *leDoctorName;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *calculator_patient)
    {
        if (calculator_patient->objectName().isEmpty())
            calculator_patient->setObjectName(QStringLiteral("calculator_patient"));
        calculator_patient->resize(606, 78);
        gridLayout = new QGridLayout(calculator_patient);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        groupBox_2 = new QGroupBox(calculator_patient);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_3->addWidget(label_12, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 0, 2, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_3->addWidget(label_11, 1, 2, 1, 1);

        leK1 = new leAddZero(groupBox_2);
        leK1->setObjectName(QStringLiteral("leK1"));
        leK1->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(leK1, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        leK2 = new leAddZero(groupBox_2);
        leK2->setObjectName(QStringLiteral("leK2"));
        leK2->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(leK2, 1, 1, 1, 1);

        line = new QFrame(groupBox_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 0, 3, 3, 1);

        leK = new leAddZero(groupBox_2);
        leK->setObjectName(QStringLiteral("leK"));
        leK->setMaximumSize(QSize(50, 16777215));
        leK->setReadOnly(true);

        gridLayout_3->addWidget(leK, 2, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        leAL_measure = new leAddZero(groupBox_2);
        leAL_measure->setObjectName(QStringLiteral("leAL_measure"));
        leAL_measure->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(leAL_measure, 0, 1, 1, 1);

        leACD_measure = new QLineEdit(groupBox_2);
        leACD_measure->setObjectName(QStringLiteral("leACD_measure"));
        leACD_measure->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(leACD_measure, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 0, 2, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_5->addWidget(label_13, 1, 2, 1, 1);

        pbSide = new QPushButton(groupBox_2);
        pbSide->setObjectName(QStringLiteral("pbSide"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbSide->sizePolicy().hasHeightForWidth());
        pbSide->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pbSide->setFont(font);

        gridLayout_5->addWidget(pbSide, 0, 3, 2, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_5, 0, 7, 3, 3);


        gridLayout->addWidget(groupBox_2, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(calculator_patient);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_4->addWidget(label_17, 1, 0, 1, 1);

        leACD_personal = new QLineEdit(groupBox_3);
        leACD_personal->setObjectName(QStringLiteral("leACD_personal"));
        leACD_personal->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(leACD_personal, 1, 1, 1, 1);

        leRx_personal = new QLineEdit(groupBox_3);
        leRx_personal->setObjectName(QStringLiteral("leRx_personal"));
        leRx_personal->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(leRx_personal, 1, 3, 1, 1);

        leSF_personal = new QLineEdit(groupBox_3);
        leSF_personal->setObjectName(QStringLiteral("leSF_personal"));
        leSF_personal->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(leSF_personal, 0, 3, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 1, 2, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 0, 0, 1, 1);

        leAConst_personal = new QLineEdit(groupBox_3);
        leAConst_personal->setObjectName(QStringLiteral("leAConst_personal"));
        leAConst_personal->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(leAConst_personal, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_4->addWidget(label_16, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 3, 1, 1);

        groupBox = new QGroupBox(calculator_patient);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lePatientId = new QLineEdit(groupBox);
        lePatientId->setObjectName(QStringLiteral("lePatientId"));
        lePatientId->setMinimumSize(QSize(150, 0));
        lePatientId->setMaximumSize(QSize(150, 16777215));
        lePatientId->setReadOnly(true);

        gridLayout_2->addWidget(lePatientId, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lePatientName = new QLineEdit(groupBox);
        lePatientName->setObjectName(QStringLiteral("lePatientName"));
        lePatientName->setMinimumSize(QSize(150, 0));
        lePatientName->setMaximumSize(QSize(150, 16777215));
        lePatientName->setReadOnly(true);

        gridLayout_2->addWidget(lePatientName, 1, 1, 1, 1);

        leDoctorName = new QLineEdit(groupBox);
        leDoctorName->setObjectName(QStringLiteral("leDoctorName"));
        leDoctorName->setMinimumSize(QSize(150, 0));
        leDoctorName->setMaximumSize(QSize(150, 16777215));
        leDoctorName->setReadOnly(true);

        gridLayout_2->addWidget(leDoctorName, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        gridLayout->setColumnStretch(0, 3);

        retranslateUi(calculator_patient);

        QMetaObject::connectSlotsByName(calculator_patient);
    } // setupUi

    void retranslateUi(QWidget *calculator_patient)
    {
        calculator_patient->setWindowTitle(QApplication::translate("calculator_patient", "Form", 0));
        groupBox_2->setTitle(QString());
        label_5->setText(QApplication::translate("calculator_patient", "K1-Value", 0));
        label_12->setText(QApplication::translate("calculator_patient", "D", 0));
        label_7->setText(QApplication::translate("calculator_patient", "K-Value", 0));
        label_10->setText(QApplication::translate("calculator_patient", "D", 0));
        label_11->setText(QApplication::translate("calculator_patient", "D", 0));
        label_6->setText(QApplication::translate("calculator_patient", "K2-Value", 0));
        leAL_measure->setText(QString());
        leACD_measure->setText(QApplication::translate("calculator_patient", "0.00", 0));
        label_9->setText(QApplication::translate("calculator_patient", "mm", 0));
        label_13->setText(QApplication::translate("calculator_patient", "mm", 0));
        pbSide->setText(QApplication::translate("calculator_patient", "OD", 0));
        label_4->setText(QApplication::translate("calculator_patient", "AL", 0));
        label_8->setText(QApplication::translate("calculator_patient", "ACD", 0));
        groupBox_3->setTitle(QString());
        label_17->setText(QApplication::translate("calculator_patient", "ACD", 0));
        label_15->setText(QApplication::translate("calculator_patient", "Rx", 0));
        label_14->setText(QApplication::translate("calculator_patient", "A Const", 0));
        label_16->setText(QApplication::translate("calculator_patient", "SF", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("calculator_patient", "Patient ID", 0));
        label_3->setText(QApplication::translate("calculator_patient", "Doctor Name", 0));
        label_2->setText(QApplication::translate("calculator_patient", "Patient Name", 0));
    } // retranslateUi

};

namespace Ui {
    class calculator_patient: public Ui_calculator_patient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_PATIENT_H
