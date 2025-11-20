//
// Created by balac on 5/29/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <string>
#include <vector>

#include "triangle.h"


class repository {
private:
    std::vector<triangle> *traingles;
    std::string filename;
public:
    repository(std::string filename);
    void load();
    void save();
    std::vector<triangle> *get_triangles_repo();
};



#endif //REPOSITORY_H
