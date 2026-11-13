#include "userwindow.h"
#include "ui_userwindow.h"
#include "adoptdog.h"
#include "QMessageBox"
#include "chart.h"
#include <vector>
#include <iostream>
userwindow::userwindow(Controller_admin &controller_admin,Controller_user &controller_user,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userwindow)
    ,controller_admin(controller_admin)
    ,controller_user(controller_user)
{
    ui->setupUi(this);
    connect(ui->DisplayDogs, &QPushButton::clicked, this, &userwindow::onDisplayDogsClicked);
    connect(ui->AdoptionList, &QPushButton::clicked,this, &userwindow::onAdoptionListClicked);
    connect(ui->pushButtonChart,&QPushButton::clicked,this, &userwindow::onChartClicked);
}

userwindow::~userwindow()
{
    delete ui;
}
void userwindow::Display(std::vector<Dog> dogs){
    std::vector<Dog> deleted_dogs;
    std::vector<int> deleted_dogs_index;
    int i=0;
    while(dogs.size()>0){
        if(i>=dogs.size()){
            //delete dogs from repo
            if(!deleted_dogs.empty()){
                for (int j = deleted_dogs.size() - 1; j >= 0; --j)
                {
                    this->controller_admin.Remove_Dog(deleted_dogs[j].get_name());
                    dogs.erase(dogs.begin() + deleted_dogs_index[j]);
                }
            }
            deleted_dogs=std::vector<Dog>();
            deleted_dogs_index=std::vector<int>();
            i=0;
        }
        else{
            Dog currentDog = dogs[i];
            adoptdog* adopt = new adoptdog(currentDog);
            adopt->setAttribute(Qt::WA_DeleteOnClose);
            connect(adopt, &adoptdog::dogAdopted, this, [=, &deleted_dogs, &deleted_dogs_index]() {
                controller_user.add_dog_adoptedlist(currentDog);
                deleted_dogs.push_back(currentDog);
                deleted_dogs_index.push_back(i);
            });
            int result = adopt->exec();
            if (result == QDialog::Rejected) {
                break;
            }
            i++;
        }
    }
}
void userwindow::onDisplayDogsClicked(){
    if( !ui->lineEditBreed->text().toStdString().empty() && !ui->lineEditAge->text().toStdString().empty()){
        //display dogs by breed and age
        std::string breed = ui->lineEditBreed->text().toStdString();
        bool ok;
        int age = ui->lineEditAge->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Input Error", "Age must be a number.");
            return;
        }
        std::vector<Dog> dogs=this->controller_user.filter_breed(this->controller_admin.get_dogs_controller(),breed);
        dogs=this->controller_user.filter_age(dogs,age);
        if(dogs.empty()){
            QMessageBox::warning(this, "Input Error", "No dog that respects your requierments");
            return;
        }
        this->Display(dogs);
    }
    else{
        if((ui->lineEditBreed->text().toStdString().empty() && !ui->lineEditAge->text().toStdString().empty()) ||
            (!ui->lineEditBreed->text().toStdString().empty() && ui->lineEditAge->text().toStdString().empty())){
            QMessageBox::warning(this, "Sorry", "Can not filter only by one characteristic");
        }
        else{
            if(this->controller_admin.get_dogs_controller().empty()){
                QMessageBox::warning(this, "Sorry", "No dog that respects your requierments");
                return;
            }
            this->Display(this->controller_admin.get_dogs_controller());
        }
    }
}

void userwindow::onAdoptionListClicked(){
    std::string cmd = "start " + this->controller_user.get_file();
    system(cmd.c_str());
}

void userwindow::onChartClicked(){
    std::vector<Dog> dogs = controller_admin.get_dogs_controller();
    std::map<QString, int> ageGroups;

    // Initialize age categories
    ageGroups["Under 5"] = 0;
    ageGroups["5-10"] = 0;
    ageGroups["Over 10"] = 0;

    for (Dog &dog : dogs) {
        int age = dog.get_age(); // assumes Dog::get_age() returns int
        if (age < 5)
            ageGroups["Under 5"]++;
        else if (age <= 10)
            ageGroups["5-10"]++;
        else
            ageGroups["Over 10"]++;
    }

    chart *c = new chart(ageGroups);
    c->setAttribute(Qt::WA_DeleteOnClose);
    c->setWindowTitle("Dogs by Age Group");
    c->show();
}
