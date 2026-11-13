#include <iostream>

#include "controller_admin.h"
#include "repo.h"
#include "ui.h"
int main() {
    Repository repo("dog_repo.txt");
    Controller_admin controller_admin(repo);
    char opt;
    std:: cout << "1 - Html\n2 - CSV\n >>> ";
    std:: cin >> opt;
    if (opt== '1') {
        std::cout << "op1\n";
        Controller_HTML controller_user(repo, "adoption_list.html");
        Ui ui(controller_admin,controller_user);
        ui.start();
    }
    else if (opt == '2') {
        Controller_CSV controller_user(repo, "adoption_list.csv");
        Ui ui(controller_admin,controller_user);
        ui.start();
    }
    else {
        std::cout<<"please enter a valid option\n";
    }
    return 0;
}

