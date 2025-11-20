/********************************************************************************
** Form generated from reading UI file 'departments.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPARTMENTS_H
#define UI_DEPARTMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_departments
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *departments)
    {
        if (departments->objectName().isEmpty())
            departments->setObjectName("departments");
        departments->resize(346, 248);
        listWidget = new QListWidget(departments);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 10, 341, 231));

        retranslateUi(departments);

        QMetaObject::connectSlotsByName(departments);
    } // setupUi

    void retranslateUi(QWidget *departments)
    {
        departments->setWindowTitle(QCoreApplication::translate("departments", "departments", nullptr));
    } // retranslateUi

};

namespace Ui {
    class departments: public Ui_departments {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPARTMENTS_H
