//
// Created by balac on 5/29/2025.
//

#ifndef EQUATION_H
#define EQUATION_H


#include <sstream>
class Equation {
private:
    double a,b,c;
public:
    Equation(double a,double b,double c);
    double get_a() const;
    double get_b() const;
    double get_c() const;
    void set_a(double a);
    void set_b(double b);
    void set_c(double c);
    int degrees();
    friend std::istream& operator>>(std::istream& is, Equation& eq);
};



#endif //EQUATION_H
