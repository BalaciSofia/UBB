//
// Created by balac on 5/29/2025.
//

#include "Equation.h"

Equation::Equation(double a, double b, double c) : a(a), b(b), c(c) {}

double Equation::get_a() const {
    return a;
}
double Equation::get_b() const {
    return b;
}
double Equation::get_c() const {
    return c;
}

void Equation::set_a(double a) {
    this->a = a;
}
void Equation::set_b(double b) {
    this->b = b;
}
void Equation::set_c(double c) {
    this->c = c;
}

int Equation::degrees() {
    if (a != 0) return 2;
    if (b != 0) return 1;
    return 0;
}
std::istream& operator>>(std::istream& is, Equation& eq) {
    if(is.peek() == '\n') is.ignore();
    std::string str;
    std::getline(is, str);
    if(str.empty()) return is;
    std::istringstream iss(str);
    std::string a,b,c;
    std::getline(iss,a, ',');
    std::getline(iss, b, ',');
    std::getline(iss, c, ',');
    eq.set_a(stod(a));
    eq.set_b(stod(b));
    eq.set_c(stod(c));
    return is;
}