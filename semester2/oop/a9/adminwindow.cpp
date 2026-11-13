#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "updatedialog.h"
#include "adddialog.h"
#include "QMessageBox"
#include <QDebug>
adminwindow::adminwindow(Controller_admin &controller_admin,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminwindow)
    ,controller_admin(controller_admin)
{
    ui->setupUi(this);
    populateTable();
}

adminwindow::~adminwindow()
{
    delete ui;
}
void adminwindow::populateTable() {
        std::vector<Dog> dogs = this->controller_admin.get_dogs_controller();
        ui->tableWidget->setRowCount(dogs.size());
        for (int i = 0; i < dogs.size(); ++i) {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dogs[i].get_name())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(dogs[i].get_age())));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(dogs[i].get_breed())));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(dogs[i].get_photograph())));
        }

}

void adminwindow::on_addButton_clicked() {
    adddialog* dialog= new adddialog(this->controller_admin, this);
    dialog->exec();
    populateTable();
}

void adminwindow::on_removeButton_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        // Get the name of the dog from the first column
        QString qName = ui->tableWidget->item(row, 0)->text();
        std::string name = qName.toStdString();

        // Remove the dog from the repository
        this->controller_admin.Remove_Dog(name);

        // Remove the row from the table
        ui->tableWidget->removeRow(row);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a row to remove.");
    }
}


void adminwindow::on_updateButton_clicked() {
    updatedialog* dialog = new updatedialog(this->controller_admin, this);
    dialog->exec();
    populateTable(); // Refresh the table after update
}
