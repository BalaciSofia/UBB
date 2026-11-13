
#include "domain.h"

School::School(std::string name, std::string address, int day, int month, int year) {
    this->name = name;
    this->address = address;
    this->day = day;
    this->month = month;
    this->year = year;
}

std::string School::getName() {
    return this->name;
}
std::string School::getAddress() {
    return this->address;
}
int School::getDay() {
    return this->day;
}
int School::getMonth() {
    return this->month;
}
int School::getYear() {
    return this->year;
}
School& School::operator=(const School& school) {
    if (this == &school)
        return *this;
    this->name = school.name;
    this->address = school.address;
    this->day = school.day;
    this->month = school.month;
    this->year = school.year;
    return *this;
}