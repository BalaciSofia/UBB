//
// Created by balac on 6/17/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AstronomerWindow.h" resolved

#include "astronomerwindow.h"
#include "ui_AstronomerWindow.h"
#include <QTableView>
#include <QVBoxLayout>
AstronomerWindow::AstronomerWindow(Astronomer astronomer,Service &service,tablemodel *model, QWidget *parent) :
    QWidget(parent), ui(new Ui::AstronomerWindow),model(model),service(service),astronomer(astronomer) {
    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString(astronomer.get_name()));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    connect(ui->checkBox, &QCheckBox::stateChanged, this, [=](int state) {
    if (state == Qt::Checked) {
        proxyModel->setFilterFixedString(QString::fromStdString(astronomer.get_constellation()));
    } else {
        proxyModel->setFilterFixedString("");
    }
});
}

AstronomerWindow::~AstronomerWindow() {
    delete ui;
}
