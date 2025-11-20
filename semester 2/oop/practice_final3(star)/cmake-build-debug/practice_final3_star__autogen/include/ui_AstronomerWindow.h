/********************************************************************************
** Form generated from reading UI file 'astronomerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASTRONOMERWINDOW_H
#define UI_ASTRONOMERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AstronomerWindow
{
public:
    QTableView *tableView;

    void setupUi(QWidget *AstronomerWindow)
    {
        if (AstronomerWindow->objectName().isEmpty())
            AstronomerWindow->setObjectName("AstronomerWindow");
        AstronomerWindow->resize(400, 300);
        tableView = new QTableView(AstronomerWindow);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(0, 0, 256, 192));

        retranslateUi(AstronomerWindow);

        QMetaObject::connectSlotsByName(AstronomerWindow);
    } // setupUi

    void retranslateUi(QWidget *AstronomerWindow)
    {
        AstronomerWindow->setWindowTitle(QCoreApplication::translate("AstronomerWindow", "AstronomerWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AstronomerWindow: public Ui_AstronomerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASTRONOMERWINDOW_H
