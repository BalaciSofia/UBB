//
// Created by balac on 6/15/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DepartmentWindow.h" resolved

#include "departmentwindow.h"

#include <iostream>
#include <QPushButton>
#include <QMessageBox>
#include "ui_DepartmentWindow.h"

DepartmentWindow::DepartmentWindow(Service &service,Department department, QWidget *parent) :
    QWidget(parent), ui(new Ui::DepartmentWindow), service(service), department(department) {
    ui->setupUi(this);
    //title
    setWindowTitle(QString::fromStdString(department.getName()));
    //description
    ui->description->setText(QString::fromStdString(department.getDescription()));

    //the lists
    for (auto &vol:this->service.volunteersForDepartment(department)) {
        ui->volunteers->addItem(QString::fromStdString(vol.toString()));
    }

    for (auto &vol:this->service.volunteersUnassigned()) {
        ui->unassigned->addItem(QString::fromStdString(vol.toString()));
    }

    connect(ui->AddButton, &QPushButton::clicked, this, &DepartmentWindow::onAddButton);
    connect(ui->AssignButton, &QPushButton::clicked, this,&DepartmentWindow::onAssignButton);
}

DepartmentWindow::~DepartmentWindow() {
    delete ui;
}

void DepartmentWindow::update() {
    ui->volunteers->clear();
    ui->unassigned->clear();
    for (auto &vol:this->service.volunteersForDepartment(department)) {
        ui->volunteers->addItem(QString::fromStdString(vol.toString()));
    }

    for (auto &vol:this->service.volunteersUnassigned()) {
        ui->unassigned->addItem(QString::fromStdString(vol.toString()));
    }
}

void DepartmentWindow::onAddButton() {
    std::string name = ui->lineEditName->text().toStdString();
    std::string email = ui->lineEditEmail->text().toStdString();
    std::string interests = ui->lineEditInterests->text().toStdString();
    if (name.empty() || email.empty()) {
        QMessageBox::warning(this, "Warning", "Name, email cannot be empty.");
        return;
    }
    this->service.addVolunteer(name, email, interests);
}

void DepartmentWindow::onAssignButton() {
    std::string vol = ui->unassigned->currentItem()->text().toStdString();
    vol=vol+",,";
    std::istringstream iss(vol);
    Volunteer volunteer;
    iss >> volunteer;
    std::cout<<volunteer.toString() << "\n";
    this->service.assignVolunteer(volunteer, this->department);
}