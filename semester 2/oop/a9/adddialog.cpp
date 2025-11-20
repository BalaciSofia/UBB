#include "adddialog.h"
#include "ui_adddialog.h"
#include "QMessageBox"
adddialog::adddialog(Controller_admin &controller_admin,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adddialog)
    , controller_admin(controller_admin)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &adddialog::onAddClicked);
}

adddialog::~adddialog()
{
    delete ui;
}

void adddialog::onAddClicked(){
    std::string Name = ui->lineEditName->text().toStdString();
    std::string Photo = ui->lineEditPhoto->text().toStdString();
    std::string Breed = ui->lineEditBreed->text().toStdString();
    try{
        bool ok;
        int age = ui->lineEditAge->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Input Error", "Age must be a number.");
            return;
        }
        this->controller_admin.Add_Dog(age,Name,Breed,Photo);
    }catch(RepositoryError &e){
        QMessageBox::warning(this, "Error", e.what());
    }catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}
