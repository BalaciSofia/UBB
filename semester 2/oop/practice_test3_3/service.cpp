//
// Created by balac on 5/29/2025.
//
#include "service.h"

#include <algorithm>
#include <iostream>

service::service(repository &r) :r(r){
    std::cout << "constructed service\n";
}

std::vector<Equation> service::get_equations_service() {
    return this->r.get_equations_repo();
}

void service::update_eq(double a, double b, double c, int index) {
    this->r.update(a,b,c,index);
}