/********************************************************************************
** Form generated from reading UI file 'updatedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDIALOG_H
#define UI_UPDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updatedialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditOldName;
    QLineEdit *lineEditNewName;
    QLineEdit *lineEditNewAge;
    QLineEdit *lineEditNewPhoto;

    void setupUi(QDialog *updatedialog)
    {
        if (updatedialog->objectName().isEmpty())
            updatedialog->setObjectName("updatedialog");
        updatedialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(updatedialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(250, 240, 121, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        horizontalLayoutWidget = new QWidget(updatedialog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 40, 351, 201));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEditOldName = new QLineEdit(horizontalLayoutWidget);
        lineEditOldName->setObjectName("lineEditOldName");

        verticalLayout->addWidget(lineEditOldName);

        lineEditNewName = new QLineEdit(horizontalLayoutWidget);
        lineEditNewName->setObjectName("lineEditNewName");

        verticalLayout->addWidget(lineEditNewName);

        lineEditNewAge = new QLineEdit(horizontalLayoutWidget);
        lineEditNewAge->setObjectName("lineEditNewAge");

        verticalLayout->addWidget(lineEditNewAge);

        lineEditNewPhoto = new QLineEdit(horizontalLayoutWidget);
        lineEditNewPhoto->setObjectName("lineEditNewPhoto");

        verticalLayout->addWidget(lineEditNewPhoto);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(updatedialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, updatedialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, updatedialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(updatedialog);
    } // setupUi

    void retranslateUi(QDialog *updatedialog)
    {
        updatedialog->setWindowTitle(QCoreApplication::translate("updatedialog", "Update dog", nullptr));
        label_5->setText(QCoreApplication::translate("updatedialog", "Original name:", nullptr));
        label->setText(QCoreApplication::translate("updatedialog", "New name:", nullptr));
        label_3->setText(QCoreApplication::translate("updatedialog", "New age:", nullptr));
        label_4->setText(QCoreApplication::translate("updatedialog", "New photo:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class updatedialog: public Ui_updatedialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDIALOG_H
