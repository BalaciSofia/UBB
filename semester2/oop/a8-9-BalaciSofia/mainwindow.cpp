#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "adminwindow.h"
#include "htmlorcsv.h"
#include "repo.h"
#include "controller_admin.h"
#include "controller_user.h"
#include "userwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_adminButton_clicked() {
    Repository* repo = new Repository("dog_repo.txt");
    Controller_admin *controller_admin = new Controller_admin(*repo);
    adminwindow *adminWin = new adminwindow(*controller_admin);
    adminWin->show();
}

void MainWindow::on_userButton_clicked(){
    htmlorcsv dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString choice = dialog.getChoice();  // e.g., "HTML" or "CSV"
        Repository* repo = new Repository("dog_repo.txt");
        Controller_admin *controller_admin = new Controller_admin(*repo);
        Controller_user* controller_user = nullptr;
        if (choice == "HTML") {
            controller_user = new Controller_HTML(*repo,std::string( "adoption_list.html"));
        } else {
            controller_user = new Controller_CSV(*repo, std::string("adoption_list.csv"));
        }
        userwindow* userWin = new userwindow(*controller_admin,*controller_user);
        userWin->show();
    }
}
