//
// Created by balac on 5/25/2025.
//

#ifndef BILL_H
#define BILL_H
#include <string>


class Bill {
private:
    std::string company_name;
    std::string serial_number;
    double sum;
    bool isPaid;
public:
    Bill()=default;
    Bill(std::string company_name, std::string serial_number, double sum, bool isPaid);
    std::string get_company_name();
    std::string get_serial_number();
    double get_sum();
    bool get_isPaid();
    void set_company_name(std::string company_name);
    void set_serial_number(std::string serial_number);
    void set_sum(double sum);
    void set_isPaid(bool isPaid);
    friend std::istream& operator>>(std::istream& is,Bill& b);
    friend std::ostream& operator<<(std::ostream& os,Bill &b);
};



#endif //BILL_H
