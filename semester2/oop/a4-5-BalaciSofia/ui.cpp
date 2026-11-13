
#include <limits>
#include "ui.h"
#include "controller_admin.h"
#include "controller_user.h"
#include "string.h"

Ui::Ui(Controller_admin &c_ad, Controller_user &c_us): controller_admin(c_ad), controller_user(c_us){}

void Ui::print_menu_admin() {
    std::cout << "============================\n";
    std::cout << "      Administrator      \n";
    std::cout << "============================\n";
    std::cout << "1. Add a new dog\n";
    std::cout << "2. Delete a dog(it was adopted)\n";
    std::cout << "3. Update dog information\n";
    std::cout << "4. Display all dogs\n";
    std::cout << "5. Exit admin mode\n";
    std::cout << "Enter your choice: ";
}

void Ui::print_menu_user() {
    std::cout << "=============================\n";
    std::cout << "         Users\n";
    std::cout << "=============================\n";
    std::cout << "1. See the dogs in the database\n";
    std::cout << "2. See all dogs of a given breed with age less than a given number\n";
    std::cout << "3. See adoption list\n";
    std::cout << "4. Exit user mode\n";
    std::cout << "Enter your choice: ";
}


void Ui::start() {
    char mode;
    while (true) {
        std::cout << "=============================\n";
        std::cout <<"type 'a' to select administrator mode\n";
        std::cout <<"type 'u' to select user mode\n";
        std::cout <<"type 'e' to exit application\n";
        std::cout<<">>>";
        std::cin >> mode;
        while (mode != 'a' && mode != 'u' && mode != 'e') {
            std::cout << "Invalid input! Please enter 'a' or 'u' or 'e'\n";
            std::cout<<">>>";
            std::cin >> mode;
        }
        std::cin.clear();
        if (mode == 'a')
            this->admin_mode();
        else if (mode == 'u')
            this->user_mode();
        else {
            std::cout <<"Exiting...\n";
            return;
        }
    }
    }


void Ui::admin_mode() {
    int opt;
    if (this->controller_admin.get_dogs_controller().getSize()==0)this->controller_admin.initial_data();
    while (true) {
        this->print_menu_admin();
        std::cin >> opt;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }
        switch (opt) {
            case 1:
                this->ui_add_dog();
            break;
            case 2:
                this->ui_delete_dog();
            break;
            case 3:
                this->ui_update_dog();
            break;
            case 4:
                this->ui_display_dogs();
            break;
            case 5:
                std::cout << "Exiting Admin Mode...\n";
            return;
            default:
                std::cout << "Invalid input! Please enter a number between 1 and 5.\n";
        }
    }
}

void Ui::ui_add_dog() {
    std::string breed, name, photograph;
    int age;
    try {
        std::cout << "Enter dog name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout<<"Enter dog breed: ";
        std::getline(std::cin, breed);
        std::cout<<"Enter dog photograph: ";
        std::getline(std::cin, photograph);
        std::cout<<"Enter dog age: ";
        std::cin>>age;
        if (std::cin.fail()) {
            std::cin.clear();
            throw std:: logic_error( "Invalid input! Please enter a valid integer for age.\n");
        }
        this->controller_admin.Add_Dog(age,name,breed,photograph);
        std::cout << "Dog added successfully!\n";
    }catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Ui::ui_delete_dog() {
    std::string name;
    try {
        std::cout << "Enter dog name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        this->controller_admin.Remove_Dog(name);
        std::cout << "Dog deleted successfully!\n";
    }catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Ui::ui_update_dog() {
    std::string name;
    int opt;
    std::cout << "Enter name of the dog you'd like to update: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (this->controller_admin.Search_name(name)==-1) {
        std::cout<<"Invalid input! Please enter a valid name!\n";
        return;
    }
    std::cout << "============================\n";
    std::cout<<"Choose what to update:\n ";
    std::cout<<"1. Name\n";
    std::cout<<"2. Age\n";
    std::cout<<"3. Photograph\n";
    std::cout<<">>>";
    std::cin>>opt;
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a valid integer.\n";
            return;
        }
        else if (opt==1) {
            std::string new_name;
            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, new_name);
            try {
                this->controller_admin.Update_name(name,new_name);
                break;
            }catch (std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (opt==2) {
            int age;
            try{
                std::cout << "Enter new age: ";
                std::cin>>age;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please enter a valid integer for age.\n";
                }
                this->controller_admin.Update_age(name,age);
                break;
            }catch (std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (opt==3) {
            std::string new_photograph;
            std::cout << "Enter new photograph: ";
            std::cin.ignore();
            std::getline(std::cin, new_photograph);
            try {
                this->controller_admin.Update_photograph(name,new_photograph);
                break;
            }catch (std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else {
            std::cout << "Invalid input! Please enter a valid option!\n";
            return;
        }
    }
}

void Ui::ui_display_dogs() {
    for (int i=0;i<this->controller_admin.get_dogs_controller().getSize();i++) {
        std::cout<<"Name: "<<this->controller_admin.get_dogs_controller()[i].get_name()<<"    ";
        std::cout<<"Breed: "<<this->controller_admin.get_dogs_controller()[i].get_breed()<<"    ";
        std::cout<<"Age: "<<this->controller_admin.get_dogs_controller()[i].get_age()<<"     ";
        std::cout<<"Photograph: "<<this->controller_admin.get_dogs_controller()[i].get_photograph()<<"\n";
    }
}

 void Ui::user_mode() {
     int opt;
     if (this->controller_admin.get_dogs_controller().getSize()==0) {
         this->controller_admin.initial_data();
     }
     while (true) {
         print_menu_user();
         std::cin >> opt;
         if (std::cin.fail()) {
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
             continue;
         }
         switch (opt) {
             case 1:
                 ui_display_database();
                 break;
             case 2:
                 ui_filter_dogs();
                 break;
             case 3:
                 ui_adoption_list();
                 break;
             case 4:
                 std::cout << "Exiting User Mode...\n";
                 return;
             default:
                 std::cout << "Invalid input! Please enter a number between 1 and 4.\n";
         }
     }
 }
 void Ui::adoption_menu() {
     std::cout<<"1->Adopt this dog\n";
     std::cout<<"2->DO NOT adopt this dog\n";
     std::cout<<"3->Exit\n";
    std::cout << "Enter your choice: ";

 }
 void Ui::ui_display_database() {
     int opt;
     int i=0,j=0;
    int length;
    length=this->controller_admin.get_dogs_controller().getSize();
    Dog dogs_to_remove[this->controller_admin.get_dogs_controller().getSize()];
     while (true) {
         ui_display_current_dog(i);
         Dog d=this->controller_user.get_current_dog_controller(i);
         adoption_menu();
         std::cin >> opt;
         if (std::cin.fail()) {
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Invalid input! Please enter a number between 1 and 5.\n";
             continue;
         }
         switch (opt) {
             case 1:
                 //adopting dog
                     this->controller_user.add_dog_adoptedlist(d);
                //remove from repo
                    dogs_to_remove[j]=d;
                    j++;
                    i++;
                if (i==length) {
                 for (int k=0; k<j;k++) {
                     this->controller_admin.Remove_Dog(dogs_to_remove[k].get_name());
                 }
                 i=0;
                 j=0;
                 length=this->controller_admin.get_dogs_controller().getSize();
                }
                 break;
             case 2:
                 i++;
             if (i==length) {
                 for (int k=0; k<j;k++) {
                     this->controller_admin.Remove_Dog(dogs_to_remove[k].get_name());
                 }
                 j=0;
                 i=0;
                 length=this->controller_admin.get_dogs_controller().getSize();
             }
                 break;
             case 3:
                 for (int k=0; k<j;k++) {
                     this->controller_admin.Remove_Dog(dogs_to_remove[k].get_name());
                 }
                 std::cout<<"Exiting Adoption process...\n";
                 return;
             default:
                 std::cout << "Invalid input! Please enter a number between 1 and 3.\n";
         }
     }
 }

 void Ui::ui_filter_dogs() {
    //filter by breed and then filter by age less than a given number
    std::string breed;
    int age;
    std::cout<<"Enter desired dog breed: ";
    std::cin.ignore();
    std::getline(std::cin, breed);
    DynamicArray<Dog> desired_dogs=this->controller_user.filter_breed(this->controller_admin.get_dogs_controller(),breed);
    std::cout<<"Enter maximum age of desired dog: ";
    std::cin>>age;
    if (std::cin.fail()) {
        std::cin.clear();
        throw std:: logic_error( "Invalid input! Please enter a valid integer for age.\n");
    }
    desired_dogs=this->controller_user.filter_age(desired_dogs,age);
    if (desired_dogs.getSize()==0) {
        std::cout<<"No such dogs. Instead take a look at:\n";
        ui_display_database();
        return;
    }
    else {
        int opt;
        int i=0,j=0;
        int length;
        length=desired_dogs.getSize();
        int dogs_to_remove[length];
        while (true) {
            if (desired_dogs.getSize()==0) {
                std::cout<<"No more dogs that respect your requirements\n";
                ui_display_database();
            }
            std::string p="start "+desired_dogs[i].get_photograph();
            std::cout<<"Name: "<<desired_dogs[i].get_name()<<"   Breed: "<<desired_dogs[i].get_breed()<<"  Age: "<<desired_dogs[i].get_age()<<"  Photograph:  "<<system(p.c_str())<<"\n";
            Dog d=desired_dogs[i];
            adoption_menu();
            std::cin >> opt;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number between 1 and 3.\n";
                continue;
            }
            switch (opt) {
                case 1:
                    //adopting dog
                        this->controller_user.add_dog_adoptedlist(d);
                    //remove from repo
                    dogs_to_remove[j]=i;
                    j++;
                    i++;
                    if (i==length) {
                        for (int k=0; k<j;k++) {
                            this->controller_admin.Remove_Dog(desired_dogs[dogs_to_remove[k]].get_name());
                            desired_dogs.remove_index(dogs_to_remove[k]);
                        }
                        length=desired_dogs.getSize();
                    i=0;
                    j=0;
                }
                break;
                case 2:
                    i++;
                if (i==length) {
                    for (int k=0; k<j;k++) {
                        this->controller_admin.Remove_Dog(desired_dogs[dogs_to_remove[k]].get_name());
                        desired_dogs.remove_index(dogs_to_remove[k]);
                    }
                    length=desired_dogs.getSize();
                    i=0;
                    j=0;
                }
                break;
                case 3:
                    for (int k=0; k<j;k++) {
                        this->controller_admin.Remove_Dog(desired_dogs[dogs_to_remove[k]].get_name());
                        desired_dogs.remove_index(dogs_to_remove[k]);
                    }
                    std::cout<<"Exiting Adoption process...\n";
                    return;
                default:
                    std::cout << "Invalid input! Please enter a number between 1 and 3.\n";
            }
        }
    }
 }

 void Ui::ui_adoption_list() {
    DynamicArray<Dog> &l=this->controller_user.get_adopted_dogs_controller();
    for (int i = 0; i < l.getSize();i++) {
        std::cout<<"Name: "<<this->controller_user.get_adopted_dogs_controller()[i].get_name()<<"    ";
        std::cout<<"Breed: "<<this->controller_user.get_adopted_dogs_controller()[i].get_breed()<<"    ";
        std::cout<<"Age: "<<this->controller_user.get_adopted_dogs_controller()[i].get_age()<<"     ";
        std::cout<<"Photograph: "<<this->controller_user.get_adopted_dogs_controller()[i].get_photograph()<<"\n";
    }
 }

 void Ui::ui_display_current_dog(int i) {
    Dog d=this->controller_user.get_current_dog_controller(i);
    std::string p="start "+d.get_photograph();
    std::cout<<"Name: "<<d.get_name()<<"  Breed: "<<d.get_breed()<<"  Age: "<<d.get_age()<<"  Photograph: "<<system(p.c_str())<<"\n";
}