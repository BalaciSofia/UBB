/********************************************************************************
** Form generated from reading UI file 'updatewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEWINDOW_H
#define UI_UPDATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updatewindow
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *updatewindow)
    {
        if (updatewindow->objectName().isEmpty())
            updatewindow->setObjectName("updatewindow");
        updatewindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(updatewindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(90, 160, 116, 18));
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(updatewindow);

        QMetaObject::connectSlotsByName(updatewindow);
    } // setupUi

    void retranslateUi(QWidget *updatewindow)
    {
        updatewindow->setWindowTitle(QCoreApplication::translate("updatewindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updatewindow: public Ui_updatewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEWINDOW_H
