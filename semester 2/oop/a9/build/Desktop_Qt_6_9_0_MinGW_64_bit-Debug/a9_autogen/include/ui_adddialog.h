/********************************************************************************
** Form generated from reading UI file 'adddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIALOG_H
#define UI_ADDDIALOG_H

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

class Ui_adddialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditName;
    QLineEdit *lineEditAge;
    QLineEdit *lineEditBreed;
    QLineEdit *lineEditPhoto;
    QLabel *label;

    void setupUi(QDialog *adddialog)
    {
        if (adddialog->objectName().isEmpty())
            adddialog->setObjectName("adddialog");
        adddialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(adddialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        horizontalLayoutWidget = new QWidget(adddialog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(40, 40, 311, 201));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEditName = new QLineEdit(horizontalLayoutWidget);
        lineEditName->setObjectName("lineEditName");

        verticalLayout_2->addWidget(lineEditName);

        lineEditAge = new QLineEdit(horizontalLayoutWidget);
        lineEditAge->setObjectName("lineEditAge");

        verticalLayout_2->addWidget(lineEditAge);

        lineEditBreed = new QLineEdit(horizontalLayoutWidget);
        lineEditBreed->setObjectName("lineEditBreed");

        verticalLayout_2->addWidget(lineEditBreed);

        lineEditPhoto = new QLineEdit(horizontalLayoutWidget);
        lineEditPhoto->setObjectName("lineEditPhoto");

        verticalLayout_2->addWidget(lineEditPhoto);


        horizontalLayout->addLayout(verticalLayout_2);

        label = new QLabel(adddialog);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 10, 331, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tahoma")});
        font.setPointSize(14);
        label->setFont(font);

        retranslateUi(adddialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, adddialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, adddialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(adddialog);
    } // setupUi

    void retranslateUi(QDialog *adddialog)
    {
        adddialog->setWindowTitle(QCoreApplication::translate("adddialog", "Add dog", nullptr));
        label_2->setText(QCoreApplication::translate("adddialog", "Name:", nullptr));
        label_4->setText(QCoreApplication::translate("adddialog", "Age:", nullptr));
        label_5->setText(QCoreApplication::translate("adddialog", "Breed:", nullptr));
        label_3->setText(QCoreApplication::translate("adddialog", "Photograph:", nullptr));
        label->setText(QCoreApplication::translate("adddialog", "Enter information of the dog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adddialog: public Ui_adddialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIALOG_H
