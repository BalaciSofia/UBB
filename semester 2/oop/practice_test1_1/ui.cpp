#include "ui.h"

Ui::Ui(Service &s):service(s){}
void Ui::print_menu() {
    std::cout<<"1:Add Station\n";
    std::cout<<"2:Show Stations\n";
    std::cout<<"3:Requirement 3\n";
    std::cout<<"4:Exit\n";
}

void Ui::add_station_ui() {
    std::string name,location,sensor;
    std::vector<std::string> sensors;
    std::cout<<"Enter Station name: ";
    std::cin>>name;
    std::cout<<"Enter Station location: ";
    std::cin>>location;
    int n;
    std::cout<<"Enter number of sensors: ";
    std::cin>>n;
    for(int i=0;i<n;i++) {
        std::cout<<"Enter sensor: ";
        std::cin>>sensor;
        sensors.push_back(sensor);
    }
    try {
        this->service.add_station_serv(location,name,sensors);
    }catch (std::exception &e) {
        std::cout<<e.what();
    }
}
void Ui::display_stations() {
    for (int i=0;i<this->service.get_station_serv().getSize();i++) {
        std::cout<<"Station "<<i<<": ";
        std::cout<<"   Location "<<this->service.get_station_serv()[i].getLocation();
        std::cout<<"   Name: "<<this->service.get_station_serv()[i].getName();
        std::cout<<"   Sensors: ";
        for (int j=0;j<service.get_station_serv()[i].getSensors().size();j++) {
            std::cout<<service.get_station_serv()[i].getSensors()[j];
            std::cout<<", ";
        }
        std::cout<<"\n";
    }
}
void Ui::sort_ui() {
    std::string sensor;
    std::cout<<"Enter Sensor type: ";
    std::cin>>sensor;
    std::vector<std::string>loc=service.locations();
    for (int i=0;i<loc.size();i++) {
        int count=this->service.count(sensor,loc[i]);
        std::cout<<"Location "<<loc[i]<<": ";
        std::cout<<count<<"\n";
    }
}
void Ui::start() {
    char opt;
    this->service.initialize();
    while (true) {
        print_menu();
        std::cout<<"choose option:";
        std::cin>>opt;
        switch (opt) {
            case '1':
                add_station_ui();
            break;
            case '2':
                display_stations();
            break;
            case '3':
                sort_ui();
            break;
            case '4':
                std::cout<<"Exiting...";
            return;
            default:
                std::cout<<"wrong option";
        }
    }
}
