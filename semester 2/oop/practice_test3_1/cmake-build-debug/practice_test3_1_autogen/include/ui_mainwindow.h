/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QListWidget *listWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QCheckBox *unpaid;
    QCheckBox *paid;

    void setupUi(QWidget *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName("mainwindow");
        mainwindow->resize(400, 300);
        listWidget = new QListWidget(mainwindow);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 10, 391, 221));
        horizontalLayoutWidget = new QWidget(mainwindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 220, 371, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        unpaid = new QCheckBox(horizontalLayoutWidget);
        unpaid->setObjectName("unpaid");

        verticalLayout->addWidget(unpaid);

        paid = new QCheckBox(horizontalLayoutWidget);
        paid->setObjectName("paid");

        verticalLayout->addWidget(paid);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QWidget *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "mainwindow", nullptr));
        label->setText(QCoreApplication::translate("mainwindow", "Company name:", nullptr));
        pushButton->setText(QCoreApplication::translate("mainwindow", "calculate total", nullptr));
        unpaid->setText(QCoreApplication::translate("mainwindow", "unpaid", nullptr));
        paid->setText(QCoreApplication::translate("mainwindow", "paid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
