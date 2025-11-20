//
// Created by balac on 5/25/2025.
//

#ifndef REPO_H
#define REPO_H
#include <vector>
#include "Bill.h"

class repo {
private:
    std::vector<Bill> *bills;
    std::string filename;
public:
    repo(std::string filename);
    std::vector<Bill> *get_bills();
    std::string get_filename();
    void add_bill(Bill bill);
    void read_bills();
    void save_bills();
};



#endif //REPO_H
