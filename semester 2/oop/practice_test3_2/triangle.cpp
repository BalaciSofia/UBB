//
// Created by balac on 5/29/2025.
//

#include "triangle.h"

#include <cmath>
#include <sstream>

triangle::triangle(double a, double b,double c):a(a),b(b),c(c){};

double triangle::area() {
    double x = (a+b+c)/2;
    double y = sqrt(x*(x-this->a)*(x-this->b)*(x-this->c));
    return y;
}

std::istream& operator >>(std::istream &is, triangle &t) {
    std::string s;
    if (is.peek() == '\n') is.ignore();
    std::getline(is, s);
    if (s.empty()) return is;
    std::istringstream iss(s);
    std::string a,b,c;
    std::getline(iss, a, ',');
    std::getline(iss, b, ',');
    std::getline(iss, c, ',');
    t.a = stod(a);
    t.b = stod(b);
    t.c = stod(c);
    return is;
}
std::ostream& operator <<(std::ostream &os, const triangle &t) {
    os << t.a << "," << t.b << "," << t.c << ",";
    return os;
}