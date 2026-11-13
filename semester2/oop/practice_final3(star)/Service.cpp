//
// Created by balac on 6/17/2025.
//

#include "Service.h"

std::vector<Astronomer> Service::get_astronomers_service() {
    return this->repo.get_astronomers();
}

std::vector<Star> Service::get_stars_service() {
    return this->repo.get_stars();
}