//
// Created by balac on 5/28/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


mainwindow::mainwindow(QWidget *parent, service &s) :s(s),
    QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    this->populateList();
    connect(ui->paid,&QCheckBox::clicked,this,&mainwindow::paidBills);
    connect(ui->unpaid, &QCheckBox::clicked, this, &mainwindow::unpaidBills);
    connect(ui->pushButton,&QPushButton::clicked,this,&mainwindow::total);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::populateList() {
    ui->listWidget->clear();
    std::vector<Bill>* bills= this->s.sorted_by_company();
    for (auto bill : *bills) {
        QString itemText = QString::fromStdString(bill.get_company_name() + " " + std::to_string(bill.get_sum()));
        QListWidgetItem *item = new QListWidgetItem(itemText, ui->listWidget);
        if (bill.get_isPaid()) {
            item->setBackground(QBrush(Qt::green));
        }
        else {
            item->setBackground(QBrush(Qt::red));
        }
        ui->listWidget->addItem(item);
    }
}

void mainwindow::paidBills() {
    ui->listWidget->clear();
    std::vector<Bill>* bills= this->s.sorted_by_company();
    for (auto bill : *bills) {
        if (bill.get_isPaid()) {
            QString itemText = QString::fromStdString(bill.get_company_name() + " " + std::to_string(bill.get_sum()));
            QListWidgetItem *item = new QListWidgetItem(itemText, ui->listWidget);
            ui->listWidget->addItem(item);
        }
    }
}

void mainwindow::unpaidBills() {
    ui->listWidget->clear();
    std::vector<Bill>* bills= this->s.sorted_by_company();
    for (auto bill : *bills) {
        if (!bill.get_isPaid()) {
            QString itemText = QString::fromStdString(bill.get_company_name() + " " + std::to_string(bill.get_sum()));
            QListWidgetItem *item = new QListWidgetItem(itemText, ui->listWidget);
            ui->listWidget->addItem(item);
        }
    }
}

void mainwindow::total() {
    try {
        std::string companyName=ui->lineEdit->text().toStdString();
        double total = this->s.CompanyTotal(companyName);
        ui->lineEdit->setText(std::to_string(total).c_str());
    }catch (std::logic_error& e) {
        QMessageBox mb;
        mb.setText(e.what());
        mb.exec();
    }
}