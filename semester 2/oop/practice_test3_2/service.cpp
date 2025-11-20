//
// Created by balac on 5/29/2025.
//

#include "service.h"
std::vector<triangle> *service::get_triangles_service() {
    return this->repo.get_triangles_repo();
}
void service::add_triangle(double a, double b, double c) {
    triangle t(a, b, c);
    this->repo.get_triangles_repo()->push_back(t);
    //this->repo.save();
}
