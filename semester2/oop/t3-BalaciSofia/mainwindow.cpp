//
// Created by balac on 5/29/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"
#include <QWidgetList>
#include <QMessageBox>
mainwindow::mainwindow(QWidget *parent,service &s) :
    s(s),QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    this->populate_list();
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &mainwindow::filterDocs);
    connect(ui->pushButton, &QPushButton::clicked, this, &mainwindow::bestMatch);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::populate_list() {
    std::vector<Document> documents=this->s.get_documents_service();
    for (auto doc : documents) {
        ui->listWidget->addItem(QString::fromStdString(doc.getName()+" with keywords:"+doc.getKeywords()));
    }
}

void mainwindow::filterDocs() {
    QString search = ui->lineEdit->text();
    ui->listWidget->clear();
    std::vector<Document> documents = this->s.get_documents_service();
    for (auto &doc : documents) {
        if (doc.getName().find(search.toStdString()) != std::string::npos ||
            doc.getKeywords().find(search.toStdString()) != std::string::npos) {
            QString itemText = QString::fromStdString(doc.getName() + " with keywords: " + doc.getKeywords());
            ui->listWidget->addItem(new QListWidgetItem(itemText));
        }
    }
}

void mainwindow::bestMatch() {
    QString search = ui->lineEdit->text();
    Document best_doc=this->s.best_match(search.toStdString());
    QMessageBox::information(this,"Best Match",QString::fromStdString(best_doc.getName()));
}
