//
// Created by balac on 5/25/2025.
//

#include "service.h"

#include <qstring.h>
#include <exception>
service::service(repo &r) : r(r) {
}

std::vector<Bill>* service::get_bills_service() {
    return this->r.get_bills();
}
std::vector<Bill>* service::sorted_by_company() {
    std::vector<Bill>* bills = this->r.get_bills();
    std::sort(bills->begin(), bills->end(), [](Bill &a,Bill &b) {
        return a.get_company_name() < b.get_company_name();
    });
    return bills;
}

double service::CompanyTotal(std::string company) {
    double total = 0;
    bool found = false;
    for (auto &bill : *this->r.get_bills()) {
        if (bill.get_company_name() == company) {
            found=true;
            total+= bill.get_sum();
        }
    }
    if (!found) {
        throw std::logic_error("Company not found");
    }
    return total;
}