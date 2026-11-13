//
// Created by balac on 6/17/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "Astronomer.h"
#include "Star.h"


class Repository {
private:
    std::string filename1,filename2;
    std::vector<Star> stars;
    std::vector<Astronomer> astronomers;
    public:
    Repository(std::string filename1, std::string filename2);

    void load();
    void save();

    std::vector<Star> get_stars();
    std::vector<Astronomer> get_astronomers();
};



#endif //REPOSITORY_H
