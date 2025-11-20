/********************************************************************************
** Form generated from reading UI file 'adoptdog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADOPTDOG_H
#define UI_ADOPTDOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adoptdog
{
public:
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAdopt;
    QPushButton *pushButtonNotAdopt;
    QLabel *labelDogImage;

    void setupUi(QDialog *adoptdog)
    {
        if (adoptdog->objectName().isEmpty())
            adoptdog->setObjectName("adoptdog");
        adoptdog->resize(700, 500);
        tableWidget = new QTableWidget(adoptdog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::NoBrush);
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(QColor(255, 194, 203));
        __qtablewidgetitem->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QBrush brush1(QColor(255, 194, 203, 255));
        brush1.setStyle(Qt::BrushStyle::NoBrush);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(12);
        font1.setBold(false);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        __qtablewidgetitem1->setForeground(brush1);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        __qtablewidgetitem2->setBackground(QColor(255, 194, 203));
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(80, 10, 511, 81));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        horizontalLayoutWidget = new QWidget(adoptdog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(150, 410, 361, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonAdopt = new QPushButton(horizontalLayoutWidget);
        pushButtonAdopt->setObjectName("pushButtonAdopt");

        horizontalLayout->addWidget(pushButtonAdopt);

        pushButtonNotAdopt = new QPushButton(horizontalLayoutWidget);
        pushButtonNotAdopt->setObjectName("pushButtonNotAdopt");

        horizontalLayout->addWidget(pushButtonNotAdopt);

        labelDogImage = new QLabel(adoptdog);
        labelDogImage->setObjectName("labelDogImage");
        labelDogImage->setGeometry(QRect(90, 110, 501, 281));
        labelDogImage->setScaledContents(true);

        retranslateUi(adoptdog);

        QMetaObject::connectSlotsByName(adoptdog);
    } // setupUi

    void retranslateUi(QDialog *adoptdog)
    {
        adoptdog->setWindowTitle(QCoreApplication::translate("adoptdog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("adoptdog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("adoptdog", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("adoptdog", "Breed", nullptr));
        pushButtonAdopt->setText(QCoreApplication::translate("adoptdog", "addopt dog", nullptr));
        pushButtonNotAdopt->setText(QCoreApplication::translate("adoptdog", "do not adopt dog", nullptr));
        labelDogImage->setText(QCoreApplication::translate("adoptdog", "dog image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adoptdog: public Ui_adoptdog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADOPTDOG_H
