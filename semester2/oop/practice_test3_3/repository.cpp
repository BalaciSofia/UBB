//
// Created by balac on 5/29/2025.
//

#include "repository.h"
#include <fstream>
#include <algorithm>

repository::repository(std::string filename) :filename(filename){
    this->load();
    sort(this->equations.begin(), this->equations.end(), [](Equation &a, Equation &b) {
        return a.get_a() < b.get_a();
    });
}
std::vector<Equation> repository::get_equations_repo() {
    return this->equations;
}
void repository::load() {
    std::ifstream file(this->filename);
    if (!file.is_open()) return;
    Equation equation(0, 0, 0);
    while (file >> equation) {
        this->equations.push_back(equation);
    }
    file.close();
}
void repository::update(double a, double b, double c, int index) {
    this->equations[index].set_a(a);
    this->equations[index].set_b(b);
    this->equations[index].set_c(c);
    sort(this->equations.begin(), this->equations.end(), [](Equation &a, Equation &b) {
    return a.get_a() < b.get_a();
});
}