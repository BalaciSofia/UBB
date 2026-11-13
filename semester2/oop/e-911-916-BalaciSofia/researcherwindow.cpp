//
// Created by balac on 6/17/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResearcherWindow.h" resolved

#include "researcherwindow.h"

#include <iostream>
#include <ranges>

#include "ui_ResearcherWindow.h"
#include <QMessageBox>

#include "devlopwindow.h"
#include "devlopwindow.h"
ResearcherWindow::ResearcherWindow(Service &service,Researcher researcher,QWidget *parent) :
    QWidget(parent), ui(new Ui::ResearcherWindow),service(service),researcher(researcher) {
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(researcher.getName()));

    ui->position->setText(QString::fromStdString(researcher.getPosition()));

    for (auto &i:this->service.getIdeas_service()) {
        ui->ideas->addItem(QString::fromStdString(i.toString()));
    }

    connect(ui->add, &QPushButton::clicked, this, &ResearcherWindow::onAddButton);
    connect(ui->accept,&QPushButton::clicked, this, &ResearcherWindow::onAcceptButton);
    connect(ui->save,&QPushButton::clicked,this,&ResearcherWindow::onSaveButton);
    connect(ui->develop,&QPushButton::clicked,this,&ResearcherWindow::onDevelopButton);


    if (this->service.hasaccepted(researcher))
        ui->develop->setEnabled(true);
    else
        ui->develop->setEnabled(false);

    if (researcher.getPosition()=="senior")
        ui->save->setEnabled(true);
    else
        ui->save->setEnabled(false);
}

void ResearcherWindow::update() {
    ui->ideas->clear();
    ui->position->setText(QString::fromStdString(researcher.getPosition()));

    for (auto &i:this->service.getIdeas_service()) {
        ui->ideas->addItem(QString::fromStdString(i.toString()));
    }
}

void ResearcherWindow::onAddButton() {
    std::string title = ui->title->text().toStdString();
    std::string description = ui->description->text().toStdString();
    std::string dur = ui->duration->text().toStdString();
    int duration= stoi(dur);
    std::string creator = this->researcher.getName();
    if (title.empty() || (duration !=1 && duration !=2 && duration !=3)) {
        QMessageBox::warning(this, "Warning", "error");
        return;
    }
    std::string status ="proposed";
    this->service.addIdea(title,description, creator,status, duration);
}

void ResearcherWindow::onAcceptButton() {
    QListWidgetItem *selectedItem = ui->ideas->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Warning", "No idea selected.");
        return;
    }

    std::string ideaString = selectedItem->text().toStdString();
    std::istringstream stream(ideaString);
    std::string title, description, creator, status, durationStr;
    int duration;

    std::getline(stream, title, ',');
    std::getline(stream, description, ',');
    std::getline(stream, creator, ',');
    std::getline(stream, status, ',');
    std::getline(stream, durationStr, ',');
    duration = std::stoi(durationStr);

    Idea selectedIdea(title, description, creator, status, duration);

    if (selectedIdea.getStatus() == "accepted") {
        QMessageBox::information(this, "Info", "This idea is already accepted.");
        ui->accept->setEnabled(false);
        return;
    }

    status = "accepted";
    this->service.UpdateStatus(selectedIdea, status);
}

void ResearcherWindow::onSaveButton() {
    std::string filename="save.txt";
    this->service.writetofile(filename);
}

void ResearcherWindow::onDevelopButton() {
    for (auto i:this->service.getIdeas_service()) {
        if (i.getStatus() == "accepted" && i.getCreator()==this->researcher.getName()) {
            auto *d= new devlopwindow(this->service,i);
            d->show();
        }
    }
}

ResearcherWindow::~ResearcherWindow() {
    delete ui;
}













