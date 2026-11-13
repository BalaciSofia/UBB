//
// Created by balac on 5/25/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"


class service {
private:
    repo &r;
public:
    service(repo &r);
    std::vector<Bill>* get_bills_service();
    std::vector<Bill>* sorted_by_company();
    double CompanyTotal(std::string company);
};



#endif //SERVICE_H
