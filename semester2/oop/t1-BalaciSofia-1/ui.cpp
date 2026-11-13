
#include "ui.h"
void Ui::print_menu() {
    std::cout<<"1.Add school\n";
    std::cout<<"2.Display schools\n";
    std::cout<<"3.Sort schools\n";
    std::cout<<"4.Exit\n";
}
void Ui::ui_addSchool() {
    std::string name,address;
    int day,month,year;
    std::cout<<"Enter school name: ";
    std::cin>>name;
    std::cout<<"Enter school address: ";
    std::cin>>address;
    std::cout<<"Enter visit day: ";
    std::cin>>day;
    std::cout<<"Enter visit month: ";
    std::cin>>month;
    std::cout<<"Enter visit year: ";
    std::cin>>year;
    try {
        this->service.addSchool_serv(name,address,day,month,year);
        std::cout<<"School added successfully\n";
    }catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void Ui::ui_display() {
    for (int i=0;i<this->service.getSchools_serv().getSize();i++) {
        std::cout<<"Name: "<<this->service.getSchools_serv()[i].getName();
        std::cout<<"   Address: "<<this->service.getSchools_serv()[i].getAddress();
        std::cout<<"   Visitation date: ";
        if (this->service.getSchools_serv()[i].getDay()<10)std::cout<<"0";
        std::cout<<this->service.getSchools_serv()[i].getDay()<<".";
        if (this->service.getSchools_serv()[i].getMonth()<10)std::cout<<"0";
        std::cout<<this->service.getSchools_serv()[i].getMonth()<<"."<<this->service.getSchools_serv()[i].getYear();
        std::cout<<"\n";
    }
}

void Ui::ui_sort() {
    DynamicArray<School> schools=this->service.sort_by_name();
    for (int i=0;i<schools.getSize();i++) {
        std::cout<<"Name: "<<schools[i].getName();
        std::cout<<"   Address: "<<schools[i].getAddress();
        std::cout<<"   Visitation date: ";
        if (schools[i].getDay()<10)std::cout<<"0";
        std::cout<<schools[i].getDay()<<".";
        if (schools[i].getMonth()<10)std::cout<<"0";
        std::cout<<schools[i].getMonth()<<"."<<schools[i].getYear();
        std::cout<<"\n";
    }
}
void Ui::start() {
    char opt;
    this->service.initialize();
    while (true) {
        print_menu();
        std::cout<<"Enter option: ";
        std::cin>>opt;
        switch (opt) {
            case '1':
                ui_addSchool();
            break;
            case '2':
                ui_display();
            break;
            case '3':
                ui_sort();
                break;
            case '4':
                std::cout<<"Exiting...\n";
            return;
            default:
                std::cout<<"Invalid option\n";
            break;
        }
    }
}