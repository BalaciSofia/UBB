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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QListWidget *listWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ab;
    QLabel *label_2;
    QLineEdit *bc;
    QLabel *label_3;
    QLineEdit *ac;
    QPushButton *addbutton;

    void setupUi(QWidget *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName("mainwindow");
        mainwindow->resize(400, 300);
        listWidget = new QListWidget(mainwindow);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 1, 391, 101));
        horizontalLayoutWidget = new QWidget(mainwindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 100, 401, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        ab = new QLineEdit(horizontalLayoutWidget);
        ab->setObjectName("ab");

        horizontalLayout->addWidget(ab);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        bc = new QLineEdit(horizontalLayoutWidget);
        bc->setObjectName("bc");

        horizontalLayout->addWidget(bc);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        ac = new QLineEdit(horizontalLayoutWidget);
        ac->setObjectName("ac");

        horizontalLayout->addWidget(ac);

        addbutton = new QPushButton(horizontalLayoutWidget);
        addbutton->setObjectName("addbutton");

        horizontalLayout->addWidget(addbutton);


        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QWidget *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "mainwindow", nullptr));
        label->setText(QCoreApplication::translate("mainwindow", "Ab:", nullptr));
        label_2->setText(QCoreApplication::translate("mainwindow", "Bc:", nullptr));
        label_3->setText(QCoreApplication::translate("mainwindow", "Ac:", nullptr));
        addbutton->setText(QCoreApplication::translate("mainwindow", "add ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
