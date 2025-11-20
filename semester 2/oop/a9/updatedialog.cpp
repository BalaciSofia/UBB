#include "updatedialog.h"
#include "ui_updatedialog.h"

#include <QMessageBox>

updatedialog::updatedialog(Controller_admin &controller_admin, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::updatedialog)
    , controller_admin(controller_admin)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &updatedialog::onUpdateClicked);
}

updatedialog::~updatedialog()
{
    delete ui;
}

void updatedialog::onUpdateClicked()
{
    std::string oldName = ui->lineEditOldName->text().toStdString();
    std::string newName = ui->lineEditNewName->text().toStdString();
    std::string photo = ui->lineEditNewPhoto->text().toStdString();
    bool ok;
    if (oldName.empty()){
        QMessageBox::warning(this, "Input Error", "Please fill in the name of the dog you intend to update.");
    }
    else{
        if (!ui->lineEditNewAge->text().toStdString().empty()){
            int age = ui->lineEditNewAge->text().toInt(&ok);
            if (!ok) {
                QMessageBox::warning(this, "Input Error", "Age must be a number.");
                return;
            }
            try{
                this->controller_admin.Update_age(oldName,age);
            }catch (RepositoryError &e) {
                QMessageBox::warning(this, "Error", e.what());
            }catch (Controller_adminError &e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        if (!photo.empty()){
            try{
                this->controller_admin.Update_photograph(oldName,photo);
            }catch (RepositoryError &e) {
                QMessageBox::warning(this, "Error", e.what());
            }catch (Controller_adminError &e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        if (!newName.empty()){
            try{
                this->controller_admin.Update_name(oldName,newName);
            }catch (RepositoryError &e) {
                QMessageBox::warning(this, "Error", e.what());
            }catch (Controller_adminError &e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
    }
}
