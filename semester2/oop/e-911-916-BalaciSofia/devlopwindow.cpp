//
// Created by balac on 6/17/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_devlopwindow.h" resolved

#include "devlopwindow.h"
#include "ui_devlopwindow.h"


devlopwindow::devlopwindow(Service &service,Idea &i,QWidget *parent) :
    QWidget(parent), ui(new Ui::devlopwindow),service(service),i(i) {
    ui->setupUi(this);
}

devlopwindow::~devlopwindow() {
    delete ui;
}
