#include "ui.h"
#include <iostream>

AdminUi::AdminUi(AdminController &controller) : controller{controller} {}

int AdminUi::read_integer() {
    std::string input;
    std::cin >> input;
    try {
        int value = std::stoi(input);
        return value;
    } catch (const std::invalid_argument&) {
        return -1;
    } catch (const std::out_of_range&) {
        return -1;
    }
}

void AdminUi::print_menu() {
    system("cls");
    std::cout << "1 - list all dogs\n";
    std::cout << "2 - add dog\n";
    std::cout << "3 - remove dog\n";
    std::cout << "4 - update dog\n";
    std::cout << "0 - exit\n";
    std::cout << "=================\n";
}

void AdminUi::list_all_dogs() const {
    std::vector<Dog> dogs = controller.get_dogs();
    if (dogs.empty()) {
        std::cout << "there are no dogs\n\n";
        return;
    }
    int index = 0;
    for (auto i : dogs) {
        std:: cout << "Dog " << index + 1 << ": ";
        std:: cout << i << "\n";
        index++;
    }
    std::cout << "\n";
}

void AdminUi::add_dog() {
    std::cout << "current list of dogs:\n";
    list_all_dogs();
    std::cout << "enter new dog (format: breed;name;age;photo link;)\n";
    Dog dog;
    try {
        std::cin >> dog;
        try {
            Validator v;
            v.validate(dog);
            controller.add_dog(dog);
        }
        catch (ValidationError e) {
            std::cout << "error: " << e.what() << "\n";
        }
    }
    catch (RepositoryError e) {
        std::cout << "error: " << e.what() << "\n";
    }
}

void AdminUi::remove_dog() {
    std::vector<Dog> dogs = controller.get_dogs();
    if (dogs.empty()) {
        std::cout << "there are no dogs to remove\n\n";
        return;
    }
    int index = 0;
    for (auto i : dogs) {
        std:: cout << "Dog " << index + 1 << ": ";
        std:: cout << i << "\n";
        index++;
    }
    std::cout << "\nindex of dog to be removed: ";
    index = read_integer();
    if(index < 1 || index > dogs.size()) {
        std::cout << "please enter a valid index\n\n";
        return;
    }
    controller.remove_dog(index-1);
    std::cout << "\n";
}

void AdminUi::update_dog() {
    std::vector<Dog> dogs = controller.get_dogs();
    if (dogs.empty()) {
        std::cout << "there are no dogs to update\n\n";
        return;
    }
    int index = 0;
    for (auto i : dogs) {
        std:: cout << "Dog " << index + 1 << ": ";
        std:: cout << i << "\n";
        index++;
    }
    std::cout << "\nindex of dog to be updated: ";
    index = read_integer();
    if(index < 1 || index > dogs.size()) {
        std::cout << "please enter a valid index\n\n";
        return;
    }
    std::cout << "what do you wish to update?\n";
    std::cout << "1 - breed\n";
    std::cout << "2 - name\n";
    std::cout << "3 - age\n";
    std::cout << "4 - photo link\n";
    std::cout << " >>> ";
    int opt = read_integer();
    switch(opt) {
        case 1: {
            std::cout << "new breed: ";
            std::cin.ignore();
            std::string breed; std::getline(std::cin, breed);
            controller.update_breed(index-1, breed);
            break;
        }
        case 2: {
            std::cout << "new name: ";
            std::cin.ignore();
            std::string name; std::getline(std::cin, name);
            controller.update_name(index-1, name);
            break;
        }
        case 3: {
            std::cout << "new age: ";
            int age = read_integer();
            if(age == -1) {
                std::cout << "please enter a valid age\n\n";
                return;
            }
            controller.update_age(index-1, age);
            break;
        }
        case 4: {
            std::cout << "new photo link: ";
            std::cin.ignore();
            std::string photo_link; std::getline(std::cin, photo_link);
            controller.update_photo_link(index-1, photo_link);
            break;
        }
        default: {
            std::cout << "please enter a valid option\n\n";
            break;
        }
    }
    std::cout << "\n";
}

void AdminUi::run() {
    while(true) {
        print_menu();
        int opt;
        std::cout << " >>> ";
        opt = read_integer();
        switch(opt) {
            case 0: {
                system("pause");
                return;
            }
            case 1: {
                list_all_dogs();
                break;
            }
            case 2: {
                add_dog();
                break;
            }
            case 3: {
                remove_dog();
                break;
            }
            case 4: {
                update_dog();
                break;
            }
            default: {
                std::cout << "please enter a valid option\n";
                break;
            }
        }
        system("pause");
    }
}

// UserUi CODE BELOW
// ==========================================================

UserUi::UserUi(UserController &controller) : controller{controller} {}

int UserUi::read_integer() {
    std::string input;
    std::cin >> input;
    try {
        int value = std::stoi(input);
        return value;
    } catch (const std::invalid_argument&) {
        return -1;
    } catch (const std::out_of_range&) {
        return -1;
    }
}

void UserUi::print_menu() {
    system("cls");
    std::cout << "1 - cycle through all dogs\n";
    std::cout << "2 - cycle through filtered dogs\n";
    std::cout << "3 - display adoption list\n";
    std::cout << "0 - exit\n";
    std::cout << "===============================\n";
}

void UserUi::open_adoption_list() {
    std::string command = "start " + controller.get_file();
    system(command.c_str());
}

void UserUi::display_adoption_list() {
    std::vector<std::pair<Dog, int>> dogs = controller.get_adoption_list();
    std::cout << "current adoption list:\n";
    if (dogs.empty())
        std::cout << "there are no dogs in the adoption list\n";
    else
        for (auto i : dogs)
            std::cout << i.first << "\n";
}

bool UserUi::display_dog(const std::pair<Dog, int>& dog_index) {
    Dog dog = dog_index.first;
    int index = dog_index.second;
    //std::string command = "start " + dog.get_photo_link();
    //system(command.c_str());
    bool exit = false;
    bool ok = false;
    while(!ok) {
        system("cls");
        display_adoption_list();
        std::cout << "\n";
        std::cout << dog << "\n";
        std::cout << "1 - adopt this dog\n";
        std::cout << "2 - do not adopt this dog\n";
        std::cout << "0 - exit\n";
        std::cout << "=========================\n";
        std::cout << " >>> ";
        int opt = read_integer();
        switch(opt) {
            case 0: {
                exit = true;
                ok = true;
                break;
            }
            case 1: {
                try {
                    controller.add_dog_to_adoption_list({dog, index});
                }
                catch (ControllerError e) {
                    std::cout << "error: " << e.what() << "\n";
                    system("pause");
                }
                exit = false;
                ok = true;
                break;
            }
            case 2: {
                exit = false;
                ok = true;
                break;
            }
            default: {
                std::cout << "please enter a valid option\n";
                system("pause");
            }
        }
    }
    return exit;
}

void UserUi::cycle_dogs(bool filtered) {
    std::vector<std::pair<Dog, int>> dogs;
    if(filtered == true) {
        std::cout << "enter breed: ";
        std::string breed; std::cin.ignore();
        std::getline(std::cin, breed);
        std::cout << "enter max age: ";
        int max_age = read_integer();
        if(max_age == -1) {
            std::cout << "please enter a valid age\n";
            return;
        }
        dogs = controller.get_filtered_dogs(breed, max_age);
    }
    else dogs = controller.get_dogs();
    if (dogs.empty()) {
        std::cout << "there are no dogs\n\n";
        return;
    }
    int current_dog_index = 0;
    while(true) {
        bool temp = display_dog(dogs[current_dog_index]);
        if(temp == true) break;
        current_dog_index++;
        if(current_dog_index == dogs.size())
            current_dog_index = 0;
    }
    controller.adopt_dogs();
}

void UserUi::run() {
    while(true) {
        print_menu();
        std::cout << " >>> ";
        int opt = read_integer();
        switch(opt) {
            case 0: {
                system("pause");
                return;
            }
            case 1: {
                cycle_dogs();
                break;
            }
            case 2: {
                cycle_dogs(true);
                break;
            }
            case 3: {
                open_adoption_list();
                break;
            }
            default: {
                std::cout << "please enter a valid option\n";
                break;
            }
        }
        system("pause");
    }
}