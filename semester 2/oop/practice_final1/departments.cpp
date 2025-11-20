//
// Created by balac on 6/15/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_departments.h" resolved

#include "departments.h"

#include "Service.h"
#include "ui_departments.h"


departments::departments(Service &service,QWidget *parent) :
    QWidget(parent), ui(new Ui::departments),service(service) {
    ui->setupUi(this);
    setWindowTitle("Departments");

    for (auto &department : service.get_departments_service()) {
        int count=this->service.numberofvolunteers(department);
        ui->listWidget->addItem(QString::fromStdString(department.getName()+" ("+std::to_string(count)+")"));
    }
}
void departments::update() {
    ui->listWidget->clear();
    for (auto &department : this->service.get_departments_service()) {
        int count=this->service.numberofvolunteers(department);
        ui->listWidget->addItem(QString::fromStdString(department.getName()+" ("+std::to_string(count)+")"));
    }
}
departments::~departments() {
    delete ui;
}
