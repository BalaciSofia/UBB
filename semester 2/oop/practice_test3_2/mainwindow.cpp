//
// Created by balac on 5/29/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"

#include <QPushButton>

#include "ui_mainwindow.h"
#include "triangle.h"
#include "QListWidgetItem"
#include "QMessageBox"

mainwindow::mainwindow(QWidget *parent, service &s) : s(s),
    QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    this->populateList();
    connect(ui->addbutton,&QPushButton::clicked,this,&mainwindow::add);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::populateList() {
    ui->listWidget->clear();
    std::vector<triangle> *tr=this->s.get_triangles_service();
    for (auto triangle:*tr) {
        QString itemText= QString::fromStdString("AB"+std::to_string(triangle.getA()) + "," +
                                                  "BC"+std::to_string(triangle.getB()) + "," +
                                                  "AC"+std::to_string(triangle.getC()) + "," +
                                                  "AREA"+std::to_string(triangle.area()));
        QListWidgetItem *item = new QListWidgetItem(itemText, ui->listWidget);
        if (triangle.area()>10) {
            item->setBackground(QBrush(Qt::green));
        }
        ui->listWidget->addItem(item);
    }
}
void mainwindow::add() {
    QString a = ui->ab->text();
    QString b = ui->bc->text();
    QString c = ui->ac->text();
    try {
        double ad = a.toDouble();
        double bd = b.toDouble();
        double cd = c.toDouble();
        this->s.add_triangle(ad,bd,cd);
        this->populateList();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Input Error", e.what());
    }
}