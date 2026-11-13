#include "ui.h"
#include "repo.h"
#include "services.h"
#include <iostream>

int main() {
    Repository repo("repo.txt");

    while(true) {
        char mode = 0;
        while(mode != 'A' && mode != 'U' && mode != '0') {
            system("cls");
            std::cout << "enter access mode (a-admin; u-user):\n";
            std::cout << "enter 0 to exit\n";
            std::cout << "==================\n";
            std::cout << " >>> ";
            std::cin >> mode;
            mode = toupper(mode);
            if(mode != 'A' && mode != 'U' && mode != '0') {
                std::cout << "please enter a valid option\n";
                system("pause");
                system("cls");
            }
        }

        switch(mode) {
            case 'A': {
                AdminController controller{repo};
                AdminUi ui{controller};
                system("cls");
                ui.run();
                break;
            }
            case 'U': {
                std::cout << "1 - Html\n2 - CSV\n >>> ";
                int opt; std::cin >> opt;
                if(opt == 1) {
                    HTMLUserController controller{repo, "adoption_list.html"};
                    UserUi ui{controller};
                    system("cls");
                    ui.run();
                }
                else if(opt == 2) {
                    CSVUserController controller{repo, "adoption_list.csv"};
                    UserUi ui{controller};
                    system("cls");
                    ui.run();
                }
                else {
                    std::cout << "please enter a valid option\n";
                    system("pause");
                    return 0;
                }
                break;
            }
            default: {
                system("pause");
                return 0;
            }
        }
    }
}