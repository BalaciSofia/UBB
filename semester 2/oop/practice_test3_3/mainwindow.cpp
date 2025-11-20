//
// Created by balac on 5/29/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"

#include <iostream>
#include <QPushButton>

#include "ui_mainwindow.h"
#include "QListWidget"


mainwindow::mainwindow(QWidget *parent,service &s) : s(s),
    QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    this->populate();
    connect(ui->pushButton,QPushButton::clicked,this,&mainwindow::update);
    connect(ui->solutions,QPushButton::clicked,this,&mainwindow::solutions);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::populate() {
    ui->listWidget->clear();
    std::cout<< "Populating list widget with equations\n";
    std::vector<Equation> eqs = this->s.get_equations_service();
    for (auto eq: eqs) {
        QString itemText;
        if (eq.degrees() == 2) {
            itemText.append(QString::fromStdString(std::to_string(eq.get_a())) + "*x^2");
        }
        if (eq.get_b() != 0) {
            itemText.append(QString::fromStdString(" + "+std::to_string(eq.get_b())) + "*x");
        }
        if (eq.get_c() != 0) {
            itemText.append(QString::fromStdString(" + "+std::to_string(eq.get_c())));
        }
        QListWidgetItem *item = new QListWidgetItem(itemText, ui->listWidget);
        ui->listWidget->addItem(item);
    }
}
void mainwindow::update() {
    int row = ui->listWidget->currentRow();
    std::string A=ui->a->text().toStdString();
    std::string B=ui->b->text().toStdString();
    std::string C=ui->c->text().toStdString();
    std::vector<Equation> eqs = this->s.get_equations_service();
    double a,b,c;
    if (A.empty())
        a=eqs[row].get_a();
    else
        a=stod(A);
    if (B.empty())
        b=eqs[row].get_b();
    else
        b=stod(B);
    if (C.empty())
        c=eqs[row].get_c();
    else
        c=stod(C);
    this->s.update_eq(a,b,c,row);
    this->populate();
}

void mainwindow::solutions() {
    int row = ui->listWidget->currentRow();
    Equation eq = this->s.get_equations_service()[row];
    double delta = eq.get_b() * eq.get_b() - 4 * eq.get_a() * eq.get_c();
    double x1 = (-eq.get_b() + sqrt(delta) )/ (2 * eq.get_a());
    double x2 = (-eq.get_b() - sqrt(delta) )/ (2 * eq.get_a());
    ui->x1->setText(QString::fromStdString(std::to_string(x1)));
    ui->x2->setText(QString::fromStdString(std::to_string(x2)));
}