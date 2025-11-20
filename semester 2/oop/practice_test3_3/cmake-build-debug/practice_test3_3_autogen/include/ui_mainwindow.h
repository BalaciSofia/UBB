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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QListWidget *listWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLineEdit *a;
    QLineEdit *b;
    QLineEdit *c;
    QPushButton *pushButton;
    QPushButton *solutions;
    QLabel *x1;
    QLabel *x2;

    void setupUi(QWidget *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName("mainwindow");
        mainwindow->resize(526, 281);
        listWidget = new QListWidget(mainwindow);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 0, 301, 241));
        horizontalLayoutWidget = new QWidget(mainwindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(319, 0, 211, 241));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        a = new QLineEdit(horizontalLayoutWidget);
        a->setObjectName("a");

        verticalLayout->addWidget(a);

        b = new QLineEdit(horizontalLayoutWidget);
        b->setObjectName("b");

        verticalLayout->addWidget(b);

        c = new QLineEdit(horizontalLayoutWidget);
        c->setObjectName("c");

        verticalLayout->addWidget(c);


        horizontalLayout->addLayout(verticalLayout);

        pushButton = new QPushButton(mainwindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(390, 250, 75, 24));
        solutions = new QPushButton(mainwindow);
        solutions->setObjectName("solutions");
        solutions->setGeometry(QRect(30, 250, 75, 24));
        x1 = new QLabel(mainwindow);
        x1->setObjectName("x1");
        x1->setGeometry(QRect(120, 260, 49, 16));
        x2 = new QLabel(mainwindow);
        x2->setObjectName("x2");
        x2->setGeometry(QRect(190, 260, 49, 16));

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QWidget *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "mainwindow", nullptr));
        label_3->setText(QCoreApplication::translate("mainwindow", "a", nullptr));
        label_2->setText(QCoreApplication::translate("mainwindow", "b", nullptr));
        label->setText(QCoreApplication::translate("mainwindow", "c", nullptr));
        pushButton->setText(QCoreApplication::translate("mainwindow", "update", nullptr));
        solutions->setText(QCoreApplication::translate("mainwindow", "compute sol", nullptr));
        x1->setText(QString());
        x2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
