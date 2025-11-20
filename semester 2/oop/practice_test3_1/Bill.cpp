//
// Created by balac on 5/25/2025.
//
#include <sstream>
#include "Bill.h"
Bill::Bill(std::string company_name, std::string serial_number, double sum, bool isPaid) {
    this->company_name = company_name;
    this->serial_number = serial_number;
    this->sum = sum;
    this->isPaid = isPaid;
}
std::string Bill::get_company_name() {
    return this->company_name;
}
std::string Bill:: get_serial_number() {
    return this->serial_number;
}
double Bill::get_sum() {
    return this->sum;
}
bool Bill::get_isPaid() {
    return this->isPaid;
}
void Bill::set_company_name (std::string company_name) {
    this->company_name = company_name;
}
void Bill::set_serial_number(std::string serial_number) {
    this->serial_number = serial_number;
}
void Bill::set_sum(double sum) {
    this->sum = sum;
}
void Bill::set_isPaid(bool isPaid) {
    this->isPaid = isPaid;
}
std::ostream& operator<<(std::ostream& os, Bill &b) {
    os << b.get_company_name()<< ';' << b.get_serial_number() << ';' << b.get_sum() << ';' << b.get_isPaid() << ';';
    return os;
}

std::istream& operator>>(std::istream& is, Bill& b) {
    if(is.peek() == '\n') is.ignore();
    std::string str;
    std::getline(is, str);
    if(str.empty()) return is;
    std::istringstream iss(str);
    std::string company_name, serial_number, sum, isPaid;
    std::getline(iss, company_name, ';');
    std::getline(iss, serial_number, ';');
    std::getline(iss, sum, ';');
    std::getline(iss, isPaid, ';');
    b.set_company_name(company_name);
    b.set_serial_number(serial_number);
    b.set_sum(stod(sum));
    b.set_isPaid((isPaid=="true"));
    return is;
}
