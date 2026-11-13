#pragma once
#include "controller_admin.h"
#include "controller_user.h"

class Ui {
private:
    Controller_admin &controller_admin;
    Controller_user &controller_user;
    void print_menu_admin();
    void print_menu_user();
    void admin_mode();
    void user_mode();
    void ui_add_dog();
    void ui_delete_dog();
    void ui_update_dog();
    void ui_display_dogs();
    void adoption_menu();
    void ui_display_database();
    void ui_filter_dogs();
    void ui_adoption_list();
    void ui_display_current_dog(int i);
    public:
    Ui(Controller_admin &c_ad, Controller_user &c_us);
    void start();
};
