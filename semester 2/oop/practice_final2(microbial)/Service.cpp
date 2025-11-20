//
// Created by balac on 6/16/2025.
//

#include "Service.h"

#include <algorithm>

Service::Service(Repository &repo) :repo(repo){

}

std::vector<Biologist> Service::get_biologists_service() {
    return this->repo.get_biologists_repo();
}
std::vector<Bacterium> Service::get_bacteriums_service() {
    return this->repo.get_bacteriums_repo();
}

std::vector<Bacterium> Service::bacteria_for_biologist(Biologist biologist) {
    std::vector<Bacterium> bacteriums;
    for (auto bact:biologist.getBacterialSpecies()) {
        for (auto bact2:this->repo.get_bacteriums_repo()) {
            if (bact == bact2.getSpecies()) {
                bacteriums.push_back(bact2);
            }
        }
    }
    std::sort(bacteriums.begin(), bacteriums.end(), [](Bacterium &a,Bacterium &b) {
        return a.getName() < b.getName();
    });
    return bacteriums;
}

void Service::addBacterium(std::string name, std::string species, int size, std::vector<std::string> diseases) {
    Bacterium bacterium(name, species, size, diseases);
    this->repo.append_bacterium(bacterium);
    this->notifyObservers();
}
