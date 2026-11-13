//
// Created by balac on 5/25/2025.
//
#include <fstream>
#include <sstream>
#include "repo.h"
repo::repo(std::string filename) {
    this->filename = filename;
    this->read_bills();
}
std::vector<Bill> *repo:: get_bills() {
    return this->bills;
}
std::string repo::get_filename() {
    return this->filename;
}
void repo::add_bill(Bill bill) {
    this->bills->push_back(bill);
}

void repo::read_bills() {
    // Read bills from the file
    this->bills = new std::vector<Bill>;
    std::ifstream file(this->filename);
    if (!file.is_open()) return;
    Bill bill;
    while (file >> bill) {
        this->bills->push_back(bill);
    }
    file.close();
}
void repo::save_bills() {
    // Save bills to the file
    std::ofstream file(this->filename);
    if (!file.is_open()) return;
    for (Bill& bill : *this->bills) {
        file << bill << std::endl;
    }
    file.close();
}