/********************************************************************************
** Form generated from reading UI file 'displaydogs.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYDOGS_H
#define UI_DISPLAYDOGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_displaydogs
{
public:

    void setupUi(QWidget *displaydogs)
    {
        if (displaydogs->objectName().isEmpty())
            displaydogs->setObjectName("displaydogs");
        displaydogs->resize(400, 300);

        retranslateUi(displaydogs);

        QMetaObject::connectSlotsByName(displaydogs);
    } // setupUi

    void retranslateUi(QWidget *displaydogs)
    {
        displaydogs->setWindowTitle(QCoreApplication::translate("displaydogs", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class displaydogs: public Ui_displaydogs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYDOGS_H
