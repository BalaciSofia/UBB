#pragma once
#include <string>

class School {
private:
    std::string name;
    std::string address;
    int day;
    int month;
    int year;
    public:
    School()=default;
    School(std::string name, std::string address, int day, int month, int year);

    std::string getName();
    std::string getAddress();
    int getDay();
    int getMonth();
    int getYear();
    School& operator=(const School& school);
};
