//
// Created by balac on 6/16/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Bacterium.h"
#include "Biologist.h"
#include <vector>
#include <string>
#include <fstream>
class Repository {
private:
    std::string filename1, filename2;
    std::vector<Bacterium> bacteriums;
    std::vector<Biologist> biologists;
public:
    Repository(std::string filename1, std::string filename2);
    void load();
    void save();
    std::vector<Bacterium> get_bacteriums_repo();
    std::vector<Biologist> get_biologists_repo();
    void append_bacterium(Bacterium bacterium);
};



#endif //REPOSITORY_H
