#pragma once
#include "services.h"
#include "dog.h"

class AdminUi {
private:
    AdminController &controller;
    static int read_integer();
    static void print_menu();
    void list_all_dogs() const;
    void add_dog();
    void remove_dog();
    void update_dog();
public:
    explicit AdminUi(AdminController &controller);
    void run();
};

class UserUi {
private:
    UserController &controller;
    static int read_integer();
    static void print_menu();
    void cycle_dogs(bool filtered = false);
    bool display_dog(const std::pair<Dog, int>& dog_index);
    void display_adoption_list();
    void open_adoption_list();
public:
    explicit UserUi(UserController &controller);
    void run();
};