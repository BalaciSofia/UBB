//
// Created by balac on 6/17/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"


class Service {
private:
    Repository &repo;
    public:
    Service(Repository &repo) : repo(repo) {}

    std::vector<Astronomer> get_astronomers_service();
    std::vector<Star> get_stars_service();
};



#endif //SERVICE_H
