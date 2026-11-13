//
// Created by balac on 5/29/2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <istream>


class triangle {
private:
    double a,b,c;
public:
    triangle(double a, double b, double c);
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double area();
    friend std::istream& operator >>(std::istream &is, triangle &t);
    friend std::ostream& operator <<(std::ostream &os, const triangle &t);
};



#endif //TRIANGLE_H
