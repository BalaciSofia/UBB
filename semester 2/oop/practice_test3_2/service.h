//
// Created by balac on 5/29/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"


class service {
private:
    repository &repo;
public:
    service(repository &repo) : repo(repo) {}
    std::vector<triangle> * get_triangles_service();
    void add_triangle(double a,double b, double c);
};




#endif //SERVICE_H
