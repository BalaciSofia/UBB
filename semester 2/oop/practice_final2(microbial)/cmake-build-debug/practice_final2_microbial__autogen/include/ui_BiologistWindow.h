/********************************************************************************
** Form generated from reading UI file 'biologistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIOLOGISTWINDOW_H
#define UI_BIOLOGISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BiologistWindow
{
public:
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *name;
    QLabel *label_4;
    QLineEdit *size;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *species;
    QLabel *label;
    QLineEdit *diseases;
    QPushButton *pushButton;

    void setupUi(QWidget *BiologistWindow)
    {
        if (BiologistWindow->objectName().isEmpty())
            BiologistWindow->setObjectName("BiologistWindow");
        BiologistWindow->resize(614, 517);
        tableWidget = new QTableWidget(BiologistWindow);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 10, 471, 391));
        comboBox = new QComboBox(BiologistWindow);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(470, 10, 141, 41));
        verticalLayoutWidget = new QWidget(BiologistWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 409, 471, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        name = new QLineEdit(verticalLayoutWidget);
        name->setObjectName("name");

        horizontalLayout_2->addWidget(name);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        size = new QLineEdit(verticalLayoutWidget);
        size->setObjectName("size");

        horizontalLayout_2->addWidget(size);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        species = new QLineEdit(verticalLayoutWidget);
        species->setObjectName("species");

        horizontalLayout->addWidget(species);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        diseases = new QLineEdit(verticalLayoutWidget);
        diseases->setObjectName("diseases");

        horizontalLayout->addWidget(diseases);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(BiologistWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(500, 420, 91, 61));

        retranslateUi(BiologistWindow);

        QMetaObject::connectSlotsByName(BiologistWindow);
    } // setupUi

    void retranslateUi(QWidget *BiologistWindow)
    {
        BiologistWindow->setWindowTitle(QCoreApplication::translate("BiologistWindow", "BiologistWindow", nullptr));
        label_3->setText(QCoreApplication::translate("BiologistWindow", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("BiologistWindow", "Size", nullptr));
        label_2->setText(QCoreApplication::translate("BiologistWindow", "Species", nullptr));
        label->setText(QCoreApplication::translate("BiologistWindow", "Diseases", nullptr));
        pushButton->setText(QCoreApplication::translate("BiologistWindow", "ADD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BiologistWindow: public Ui_BiologistWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIOLOGISTWINDOW_H
