/********************************************************************************
** Form generated from reading UI file 'departmentwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPARTMENTWINDOW_H
#define UI_DEPARTMENTWINDOW_H

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

class Ui_DepartmentWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *hboxLayout;
    QListWidget *volunteers;
    QListWidget *unassigned;
    QLabel *description;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditName;
    QLineEdit *lineEditEmail;
    QLineEdit *lineEditInterests;
    QPushButton *AddButton;
    QPushButton *AssignButton;

    void setupUi(QWidget *DepartmentWindow)
    {
        if (DepartmentWindow->objectName().isEmpty())
            DepartmentWindow->setObjectName("DepartmentWindow");
        DepartmentWindow->resize(696, 478);
        horizontalLayoutWidget = new QWidget(DepartmentWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 40, 691, 301));
        hboxLayout = new QHBoxLayout(horizontalLayoutWidget);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        volunteers = new QListWidget(horizontalLayoutWidget);
        volunteers->setObjectName("volunteers");

        hboxLayout->addWidget(volunteers);

        unassigned = new QListWidget(horizontalLayoutWidget);
        unassigned->setObjectName("unassigned");

        hboxLayout->addWidget(unassigned);

        description = new QLabel(DepartmentWindow);
        description->setObjectName("description");
        description->setGeometry(QRect(0, 10, 421, 31));
        horizontalLayoutWidget_2 = new QWidget(DepartmentWindow);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(0, 340, 351, 101));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEditName = new QLineEdit(horizontalLayoutWidget_2);
        lineEditName->setObjectName("lineEditName");

        verticalLayout->addWidget(lineEditName);

        lineEditEmail = new QLineEdit(horizontalLayoutWidget_2);
        lineEditEmail->setObjectName("lineEditEmail");

        verticalLayout->addWidget(lineEditEmail);

        lineEditInterests = new QLineEdit(horizontalLayoutWidget_2);
        lineEditInterests->setObjectName("lineEditInterests");

        verticalLayout->addWidget(lineEditInterests);


        horizontalLayout->addLayout(verticalLayout);

        AddButton = new QPushButton(DepartmentWindow);
        AddButton->setObjectName("AddButton");
        AddButton->setGeometry(QRect(0, 440, 121, 41));
        AssignButton = new QPushButton(DepartmentWindow);
        AssignButton->setObjectName("AssignButton");
        AssignButton->setGeometry(QRect(540, 350, 151, 41));

        retranslateUi(DepartmentWindow);

        QMetaObject::connectSlotsByName(DepartmentWindow);
    } // setupUi

    void retranslateUi(QWidget *DepartmentWindow)
    {
        DepartmentWindow->setWindowTitle(QCoreApplication::translate("DepartmentWindow", "DepartmentWindow", nullptr));
        description->setText(QString());
        label_3->setText(QCoreApplication::translate("DepartmentWindow", "name", nullptr));
        label_2->setText(QCoreApplication::translate("DepartmentWindow", "email", nullptr));
        label->setText(QCoreApplication::translate("DepartmentWindow", "interests", nullptr));
        AddButton->setText(QCoreApplication::translate("DepartmentWindow", "ADD", nullptr));
        AssignButton->setText(QCoreApplication::translate("DepartmentWindow", "ASSIGN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DepartmentWindow: public Ui_DepartmentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPARTMENTWINDOW_H
