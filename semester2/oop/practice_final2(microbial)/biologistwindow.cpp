//
// Created by balac on 6/16/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BiologistWindow.h" resolved

#include "biologistwindow.h"

#include <iostream>

#include "ui_BiologistWindow.h"
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

BiologistWindow::BiologistWindow(Service &service, Biologist biologist,QWidget *parent) :
    QWidget(parent), ui(new Ui::BiologistWindow),service(service), biologist(biologist) {
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(biologist.getName()));
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Name", "Species", "Size", "Diseases"});
    std::vector<Bacterium> bacteriums=this->service.bacteria_for_biologist(biologist);
    std::cout<< "Number of bacteriums: " << bacteriums.size() << "\n";
    ui->tableWidget->setRowCount(bacteriums.size());
    for (int i = 0; i < bacteriums.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getName())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getSpecies())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(bacteriums[i].getSize())));
        std::vector<std::string> diseases = bacteriums[i].getDiseases();
        std::ostringstream oss;
        for (int j = 0; j < diseases.size(); ++j) {
            oss << diseases[j];
            if (j < diseases.size() - 1) {
                oss << "; ";
            }
        }
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(oss.str())));
    }

    ui->comboBox->setEditable(false);
    ui->comboBox->addItem("All Species");
    for (auto &bact: biologist.getBacterialSpecies()) {
        ui->comboBox->addItem(QString::fromStdString(bact));
    }
    connect(ui->pushButton, &QPushButton::clicked, this, &BiologistWindow::onAddButtonClicked);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BiologistWindow::onComboBoxSelectionChanged);
}
void BiologistWindow::update() {
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Name", "Species", "Size", "Diseases"});
    std::vector<Bacterium> bacteriums=this->service.bacteria_for_biologist(biologist);

    ui->tableWidget->setRowCount(bacteriums.size());
    for (int i = 0; i < bacteriums.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getName())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getSpecies())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(bacteriums[i].getSize())));
        std::vector<std::string> diseases = bacteriums[i].getDiseases();
        std::ostringstream oss;
        for (int j = 0; j < diseases.size(); ++j) {
            oss << diseases[j];
            if (j < diseases.size() - 1) {
                oss << "; ";
            }
        }
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(oss.str())));
    }
}

void BiologistWindow::onComboBoxSelectionChanged(int index) {
    ui->tableWidget->clear();
    if (index >= 0) {
        QString selectedItem = ui->comboBox->itemText(index);
        std::cout << "Selected item: " << selectedItem.toStdString() << std::endl;
        std::string selectedSpecies = selectedItem.toStdString();
        std::vector<Bacterium> bacteriums=this->service.bacteria_for_biologist(biologist);
        std::vector<Bacterium> new_bacteriums;
        for (int i = 0; i < bacteriums.size(); ++i) {
            if (selectedSpecies == bacteriums[i].getSpecies()) {
                new_bacteriums.push_back(bacteriums[i]);
            }
        }
        if (new_bacteriums.empty())bacteriums= this->service.bacteria_for_biologist(biologist);
        else bacteriums= new_bacteriums;
        for (int i = 0; i < bacteriums.size(); ++i) {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getName())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(bacteriums[i].getSpecies())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(bacteriums[i].getSize())));
            std::vector<std::string> diseases = bacteriums[i].getDiseases();
            std::ostringstream oss;
            for (int j = 0; j < diseases.size(); ++j) {
                oss << diseases[j];
                if (j < diseases.size() - 1) {
                    oss << "; ";
                }
            }
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(oss.str())));
        }
    }
}

void BiologistWindow::onAddButtonClicked() {
    std::string name = ui->name->text().toStdString();
    std::string species = ui->species->text().toStdString();
    int size = ui->size->text().toInt();
    std::string diseases = ui->diseases->text().toStdString();
    std::vector<std::string> diseaseList;
    std::istringstream iss(diseases);
    std::string disease;
    while (iss >> disease) {
        diseaseList.push_back(disease);
    }
    try {
        this->service.addBacterium(name, species, size, diseaseList);
    }catch (std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        return;
    }

}
BiologistWindow::~BiologistWindow() {
    delete ui;
}
